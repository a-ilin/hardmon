#include "hardmon/CSensorReader.hpp"
#include "hardmon/Utils.hpp"
#include "hardmon/sensor/CSensorFactory.hpp"

#include <iostream>

#include <yaml-cpp/yaml.h>


namespace hardmon
{

CSensorReader::WorkerThread::WorkerThread(const char *threadName)
    : workGuard(boost::asio::make_work_guard(context))
    , thread([this](){ context.run(); })
{
    if(pthread_setname_np(thread.native_handle(), threadName)) {
        std::cerr << "Failed to set thread name: " << threadName << std::endl;
    }
}

CSensorReader::CSensorReader(const std::shared_ptr<IStorage> &storage, size_t threadCount)
    : m_storage(storage)
    , m_isStopping(false)
{
    for (size_t i = 0; i < threadCount; ++i) {
        m_workers.push_back(std::make_unique<WorkerThread>(string_format("sensor_reader_%d", i).c_str()));
    }
}

CSensorReader::~CSensorReader()
{
    stop();
}

void CSensorReader::configureSensors(const YAML::Node &configSensors) noexcept(false)
{
    assert(m_sensors.size() == 0);

    m_sensors.reserve(configSensors.size());

    for (YAML::const_iterator it = configSensors.begin(); it != configSensors.end(); ++it) {
        YAML::Node node = *it;

        try {
            std::string type = node["sensor"].as<std::string>();
            std::string id = node["id"].as<std::string>();

            uint64_t intervalRaw = node["interval"].as<uint64_t>();
            auto interval = TSensorInterval(intervalRaw);

            YAML::Node params = node["params"];

            auto sensor = CSensorFactory::createSensor(type, params);

            m_sensors.push_back({
                                 .sensor = sensor,
                                 .id = id,
                                 .interval = interval,
                                 .timer = {},
            });

            m_storage->setSensorAttributes(id, {
                                                .freqHz = sensorFrequency(sensor, interval),
                                                .interval = interval,
                                                });
        } catch (const std::exception& ex) {
            throw std::runtime_error(string_format("error on configuration of sensor #%d: %s",
                                                   std::distance(configSensors.begin(), it),
                                                   ex.what()));
        }
    }
}

void CSensorReader::start()
{
    for (size_t i = 0; i < m_sensors.size(); ++i) {
        // A simple round-robin strategy for scheduling.
        WorkerThread& worker = *m_workers[i % m_workers.size()];
        SensorEntry& entry = m_sensors[i];

        entry.timer = std::make_unique<boost::asio::deadline_timer>(worker.context);

        scheduleSensor(entry);
    }
}

void CSensorReader::stop()
{
    if (!m_isStopping.exchange(true)) {
        m_isStopping = true;

        // cancel jobs
        for (auto& worker : m_workers) {
            worker->workGuard.reset();
        }

        // wait for threads
        for (auto& worker : m_workers) {
            worker->thread.join();
        }
    }
}

void CSensorReader::scheduleSensor(SensorEntry &entry)
{
    auto handler = [this, &entry](const boost::system::error_code& error) {
        if (boost::asio::error::operation_aborted == error) {
            return;
        }

        TSensorValue value = entry.sensor->measure();

        {
            std::scoped_lock lock(m_storageLocker);
            m_storage->appendValue(entry.id, value);
        }

        std::cout << entry.id << ": " << value << std::endl;

        if (!m_isStopping) {
            scheduleSensor(entry);
        }
    };

    entry.timer->expires_from_now(entry.interval);
    entry.timer->async_wait(handler);
}

TSensorFrequency CSensorReader::sensorFrequency(const std::shared_ptr<ISensor> &sensor,
                                                const TSensorInterval &interval)
{
    TSensorFrequency freqHz = static_cast<TSensorFrequency>(0);

    try {
        freqHz = sensor->frequency();
    } catch(const std::runtime_error&) {
    }

    if (freqHz == static_cast<TSensorFrequency>(0)) {
        // By default use frequency defined by the specified interval.
        freqHz = static_cast<TSensorFrequency>(1000) / interval.total_milliseconds();
    }

    return freqHz;
}

}

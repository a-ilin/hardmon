#pragma once

#include "hardmon/sensor/ISensor.hpp"
#include "hardmon/storage/IStorage.hpp"

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>


namespace YAML {
class Node;
}

namespace hardmon
{

class CSensorReader
{
    struct SensorEntry
    {
        std::shared_ptr<ISensor> sensor;
        std::string id;
        TSensorInterval interval;
        std::unique_ptr<boost::asio::deadline_timer> timer;
    };

    struct WorkerThread
    {
        WorkerThread(const char* threadName);

        boost::asio::io_context context;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard;
        std::thread thread;
    };

public:
    explicit CSensorReader(const std::shared_ptr<IStorage>& storage, size_t threadCount = 1);
    ~CSensorReader();

    void configureSensors(const YAML::Node& configSensors) noexcept(false);

    void start();
    void stop();

protected:
    void scheduleSensor(SensorEntry& entry);

    static TSensorFrequency sensorFrequency(const std::shared_ptr<ISensor>& sensor,
                                            const TSensorInterval& interval);

private:
    std::mutex m_storageLocker;
    std::shared_ptr<IStorage> m_storage;
    std::vector<std::unique_ptr<WorkerThread>> m_workers;
    std::vector<SensorEntry> m_sensors;
    std::atomic_bool m_isStopping;
};

}

#include "hardmon/sensor/CSensorFactory.hpp"
#include "hardmon/Utils.hpp"
#include "hardmon/sensor/CSensorRegularFile.hpp"
#include "hardmon/sensor/CSensorSndFile.hpp"

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace hardmon {

template<class T>
struct SensorCtor
{
    std::shared_ptr<ISensor> operator()(const YAML::Node& configSensorParam) const
    {
        return std::make_shared<T>(configSensorParam);
    }
};

std::shared_ptr<ISensor> CSensorFactory::createSensor(const std::string& type,
                                                      const YAML::Node& configSensorParam) noexcept(false)
{
    using SensorCtorFunc = std::function<std::shared_ptr<ISensor>(const YAML::Node&)>;

    static const std::unordered_map<std::string, SensorCtorFunc> factories = {
        { "regular-file", SensorCtor<CSensorRegularFile>() },
        { "snd-file", SensorCtor<CSensorSndFile>() },
    };

    try {
        SensorCtorFunc ctor = factories.at(type);
        return ctor(configSensorParam);
    } catch (const std::out_of_range&) {
        throw std::runtime_error(string_format("unknown sensor: %s", type.c_str()));
    } catch (const std::exception& ex) {
        throw std::runtime_error(string_format("error on sensor initialization: %s: %s", type.c_str(), ex.what()));
    }
}

} // namespace hardmon

#pragma once

#include "hardmon/sensor/ISensor.hpp"

#include <memory>

namespace YAML {
class Node;
}

namespace hardmon
{

class CSensorFactory
{
public:
    static std::shared_ptr<ISensor> createSensor(const std::string& type, const YAML::Node& configSensorParam) noexcept(false);
};

}

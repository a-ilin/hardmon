#pragma once

#include "hardmon/sensor/ISensor.hpp"

#include <memory>

namespace YAML {
class Node;
}

namespace hardmon {

/*!
 * \brief The CSensorFactory class instantiates sensors.
 *
 * All sensor types must be registered in the factory.
 */
class CSensorFactory
{
public:
    static std::shared_ptr<ISensor> createSensor(const std::string& type,
                                                 const YAML::Node& configSensorParam) noexcept(false);
};

} // namespace hardmon

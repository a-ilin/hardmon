#pragma once

#include "hardmon/sensor/ISensor.hpp"
#include <string>

namespace YAML {
class Node;
}

namespace hardmon
{

/*!
 * \brief The CSensorRegularFile class represents a sensor reading a single values from a file.
 *
 * The sensor opens file only during call to \a measure function.
 * This makes this sensor suitable for reading of system characteristics, such as CPU frequency,
 * FAN speed, temperature, etc.
 *
 * Supported config parameters:
 * - filename: string, path to the file to read
 */
class CSensorRegularFile : public ISensor
{
public:
    CSensorRegularFile(const YAML::Node& configSensorParam);

    // ISensor
    TSensorFrequency frequency() const noexcept(false) override;
    TSensorValue measure() const noexcept(false) override;

private:
    const std::string m_fileName;
};

}

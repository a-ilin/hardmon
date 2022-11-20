#pragma once

#include "hardmon/sensor/ISensor.hpp"
#include <string>

namespace YAML {
class Node;
}

namespace hardmon
{

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

#include "hardmon/sensor/CSensorRegularFile.hpp"
#include "hardmon/Utils.hpp"

#include <yaml-cpp/yaml.h>

#include <fstream>
#include <iostream>

namespace hardmon {

CSensorRegularFile::CSensorRegularFile(const YAML::Node& configSensorParam)
    : m_fileName(configSensorParam["filename"].as<std::string>())
{
}

TSensorFrequency CSensorRegularFile::frequency() const noexcept(false)
{
    return 0;
}

TSensorValue CSensorRegularFile::measure() const noexcept(false)
{
    std::ifstream file(m_fileName);
    if (!file.is_open()) {
        throw std::runtime_error(string_format("cannot open file: %s", m_fileName.c_str()));
    }

    TSensorValue result = 0.0;
    file >> result;

    return result;
}

} // namespace hardmon

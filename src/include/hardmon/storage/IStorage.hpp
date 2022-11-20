#pragma once

#include "hardmon/Types.hpp"

#include <string>

namespace hardmon
{


class IStorage
{
public:
    struct SensorAttributes
    {
        // Frequency, Hz
        TSensorFrequency freqHz = 0;

        TSensorInterval interval = TSensorInterval(0);
    };

public:
    virtual ~IStorage() {}

    // set sensor attributes
    virtual void setSensorAttributes(const std::string& tag, const SensorAttributes& attr) = 0;

    // add measurement
    virtual void appendValue(const std::string& tag, const TSensorValue& value) = 0;
};


}

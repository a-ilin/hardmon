#pragma once

#include "hardmon/Types.hpp"

#include <string>

namespace hardmon {

/*!
 * \brief The IStorage class is a base class for storages.
 */
class IStorage
{
public:
    /*!
     * \brief The SensorAttributes class represents stored attributes of a sensor.
     */
    struct SensorAttributes
    {
        /*!
         * \brief freqHz sensor frequency, in Hz
         */
        TSensorFrequency freqHz = 0;

        /*!
         * \brief interval sensor measurement interval
         */
        TSensorInterval interval = TSensorInterval(0);
    };

public:
    virtual ~IStorage() {}

    /*!
     * \brief Sets attributes for a specified sensor identifier.
     * \param tag sensor identifier
     * \param attr attributes
     */
    virtual void setSensorAttributes(const std::string& tag, const SensorAttributes& attr) = 0;

    /*!
     * \brief Add sensor measurement value into the storage.
     * \param tag sensor identifier
     * \param value sensor measurement value
     */
    virtual void appendValue(const std::string& tag, const TSensorValue& value) = 0;
};

} // namespace hardmon

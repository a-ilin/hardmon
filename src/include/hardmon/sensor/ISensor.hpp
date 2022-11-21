#pragma once

#include "hardmon/Types.hpp"

namespace hardmon {

/*!
 * \brief The ISensor class is a base class for sensors.
 */
class ISensor
{
public:
    virtual ~ISensor() {}

    /*!
     * \brief Returns sample rate of the underlying signal.
     *
     * \return Sample rate in Hz.
     *
     * In case of sample rate is not known, the function must return 0
     * or throw an exception of type std::runtime_error.
     *
     * The function is guaranteed to be called before any measurement.
     */
    virtual TSensorFrequency frequency() const noexcept(false) = 0;

    /*!
     * \brief Returns current value of the signal.
     *
     * \return Signal value
     */
    virtual TSensorValue measure() const noexcept(false) = 0;
};

} // namespace hardmon

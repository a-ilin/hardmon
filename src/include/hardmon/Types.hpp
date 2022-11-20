#pragma once

#include <boost/date_time/posix_time/posix_time_duration.hpp>


namespace hardmon
{

/*!
 * Type for sensor values.
 */
using TSensorValue = double;

/*!
 * Type for sensor carrier frequency.
 */
using TSensorFrequency = double;

/*!
 * Type for sensor readings interval.
 */
using TSensorInterval = boost::posix_time::milliseconds;

}

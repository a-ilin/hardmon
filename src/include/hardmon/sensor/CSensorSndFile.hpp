#pragma once

#include "hardmon/sensor/ISensor.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <memory>

namespace YAML {
class Node;
}

class SndfileHandle;

namespace hardmon {

/*!
 * \brief The CSensorSndFile class represents a sensor reading frames from a sound file.
 *
 * The sensor imitates measuring a file during playback.
 *
 * Supported config parameters:
 * - filename: string, path to the file to read
 * - channel: int (default: 0), index of channel to measure
 * - skip-millisec: int (default: 0), skip specified amount of milliseconds from the beginning of the file
 */
class CSensorSndFile : public ISensor
{
public:
    CSensorSndFile(const YAML::Node& configSensorParam);
    ~CSensorSndFile() override;

    // ISensor
    TSensorFrequency frequency() const noexcept(false) override;
    TSensorValue measure() const noexcept(false) override;

private:
    void seek(const boost::posix_time::milliseconds& value);
    void advanceCurrentPosition();

private:
    std::unique_ptr<SndfileHandle> m_sndFile;
    boost::posix_time::milliseconds m_skipDuration;
    boost::posix_time::ptime m_startTime;
    int m_channel;
};

} // namespace hardmon

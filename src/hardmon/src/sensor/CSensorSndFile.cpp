#include "hardmon/sensor/CSensorSndFile.hpp"
#include "hardmon/Utils.hpp"

#include <sndfile.hh>
#include <yaml-cpp/yaml.h>

namespace hardmon {

CSensorSndFile::CSensorSndFile(const YAML::Node& configSensorParam)
    : m_sndFile(std::make_unique<SndfileHandle>(configSensorParam["filename"].as<std::string>()))
    , m_skipDuration(boost::posix_time::milliseconds(0))
    , m_channel(0)
{
    // check status
    if (m_sndFile->error()) {
        throw std::runtime_error(string_format("cannot open file: %s", m_sndFile->strError()));
    }

    // configure channels
    try {
        m_channel = configSensorParam["channel"].as<int>();
    } catch (const std::exception&) {
        // ignore, use default value
    }

    if (m_sndFile->channels() <= m_channel) {
        throw std::runtime_error(string_format(
          "configured channel index is higher than available channels: %d > %d", m_channel, m_sndFile->channels()));
    }

    // skip specified milliseconds
    try {
        int skipMillisec = configSensorParam["skip-millisec"].as<int>();
        m_skipDuration = boost::posix_time::milliseconds(skipMillisec);
    } catch (const std::exception&) {
        // ignore, use default value
    }

    m_startTime = boost::posix_time::microsec_clock::universal_time();
}

CSensorSndFile::~CSensorSndFile() {}

TSensorFrequency CSensorSndFile::frequency() const noexcept(false)
{
    return m_sndFile->samplerate();
}

TSensorValue CSensorSndFile::measure() const noexcept(false)
{
    const_cast<CSensorSndFile*>(this)->advanceCurrentPosition();

    std::vector<TSensorValue> v(m_sndFile->channels());
    m_sndFile->read(&v[0], v.size());

    return v[m_channel];
}

void CSensorSndFile::seek(const boost::posix_time::milliseconds& value)
{
    // NOTE: sndfile seeks for all channels at once
    size_t offset = m_sndFile->samplerate() / 1000 * value.total_milliseconds();
    m_sndFile->seek(offset, SEEK_SET);
}

void CSensorSndFile::advanceCurrentPosition()
{
    auto now = boost::posix_time::microsec_clock::universal_time();
    auto diff = now - m_startTime + m_skipDuration;
    seek(boost::posix_time::milliseconds(diff.total_milliseconds()));
}

} // namespace hardmon

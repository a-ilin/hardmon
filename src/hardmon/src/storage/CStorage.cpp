#include "hardmon/storage/CStorage.hpp"

#include <highfive/H5Easy.hpp>

namespace hardmon
{

CStorage::CStorage(const std::string &fileName)
    : m_fileName(fileName)
{
}

void CStorage::setSensorAttributes(const std::string &tag, const SensorAttributes &attr)
{
    m_data[tag].first = attr;
}

void CStorage::appendValue(const std::string &tag, const TSensorValue &value)
{
    auto& container = m_data[tag].second;
    container.push_back(value);
}

const IStorage::SensorAttributes &CStorage::sensorAttributes(const std::string &tag) const
{
    return m_data.at(tag).first;
}

const CStorage::Container& CStorage::values(const std::string &tag) const
{
    return m_data.at(tag).second;
}

void CStorage::saveAll()
{
    H5Easy::File file(m_fileName, HighFive::File::Overwrite);

    for (auto it = m_data.cbegin(); it != m_data.cend(); ++it) {
        saveEntry(it->first, it->second);
    }
}

void CStorage::loadAll()
{
    throw std::runtime_error("Not implemented");
}

void CStorage::save(const std::string &tag)
{
    saveEntry(tag, m_data[tag]);
}

void CStorage::load(const std::string &tag)
{
    H5Easy::File file(m_fileName, HighFive::File::ReadOnly);
    auto& readings = m_data[tag];

    readings.second = H5Easy::load<Container>(file, "/" + tag);

    // load attributes
    readings.first.freqHz = H5Easy::loadAttribute<TSensorFrequency>(file, "/" + tag, "freq");
    readings.first.interval = TSensorInterval(H5Easy::loadAttribute<uint64_t>(file, "/" + tag, "interval"));
}

void CStorage::saveEntry(const std::string& tag, const StorageEntry& entry) const
{
    H5Easy::File file(m_fileName, HighFive::File::ReadWrite);
    H5Easy::dump(file, "/" + tag, entry.second);

    // write attributes
    H5Easy::dumpAttribute(file, "/" + tag, "freq", entry.first.freqHz);
    H5Easy::dumpAttribute(file, "/" + tag, "interval", entry.first.interval.total_milliseconds());
}

}


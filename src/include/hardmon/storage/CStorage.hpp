#pragma once

#include "hardmon/storage/IStorage.hpp"
#include "hardmon/Types.hpp"

#include <string>
#include <unordered_map>
#include <vector>


namespace hardmon
{


class CStorage : public IStorage
{
public:
    using Container = std::vector<TSensorValue>;
    using StorageEntry = std::pair<SensorAttributes, Container>;

public:
    CStorage(const std::string& fileName);

    // set sensor attributes
    void setSensorAttributes(const std::string& tag, const SensorAttributes& attr) override;
    // add measurement
    void appendValue(const std::string& tag, const TSensorValue& value) override;

    // retreive attributes
    const SensorAttributes& sensorAttributes(const std::string& tag) const;
    // retreive measurements
    const Container& values(const std::string& tag) const;

    // disk I/O
    void saveAll();
    void loadAll();
    void save(const std::string& tag);
    void load(const std::string& tag);

private:
    void saveEntry(const std::string& tag, const StorageEntry& entry) const;

private:
    std::string m_fileName;
    std::unordered_map<std::string, StorageEntry> m_data;
};


}

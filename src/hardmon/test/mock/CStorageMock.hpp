#pragma once

#include "hardmon/storage/IStorage.hpp"

#include <gmock/gmock.h>


class CStorageMock : public hardmon::IStorage
{
public:
    MOCK_METHOD2(setSensorAttributes, void(const std::string&, const hardmon::IStorage::SensorAttributes&));
    MOCK_METHOD2(appendValue, void(const std::string&, const hardmon::TSensorValue&));
};

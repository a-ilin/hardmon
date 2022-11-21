#pragma once

#include "hardmon/plotfile/CPlotFileBase.hpp"

#include <string>

namespace hardmon {

class CGnuPlotFile : public CPlotFileBase
{
public:
    void writeData(const std::string& fileName,
                   const std::vector<TSensorFrequency>& xValues,
                   const std::vector<TSensorValue>& yValues) override;
};

} // namespace hardmon

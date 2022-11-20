#pragma once

#include "hardmon/Types.hpp"

#include <string>
#include <vector>

namespace hardmon
{

class CPlotFileBase
{
public:
    virtual ~CPlotFileBase() {}

    virtual void writeData(const std::string& fileName,
                           const std::vector<TSensorFrequency>& xValues,
                           const std::vector<TSensorValue>& yValues) = 0;

    const std::string& title() const { return m_title; }
    void setTitle(const std::string& title) { m_title = title; }

    const std::string& xLabel() const { return m_xLabel; }
    void setXLabel(const std::string& label) { m_xLabel = label; }

    const std::string& yLabel() const { return m_yLabel; }
    void setYLabel(const std::string& label) { m_yLabel = label; }

    bool linesPoints() const { return m_linesPoints; }
    void setLinesPoints(bool v) { m_linesPoints = v; }

protected:
    std::string m_fileName;
    std::string m_title;
    std::string m_xLabel;
    std::string m_yLabel;
    bool m_linesPoints = false;
};

}

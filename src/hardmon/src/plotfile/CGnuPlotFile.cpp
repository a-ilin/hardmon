#include "hardmon/plotfile/CGnuPlotFile.hpp"
#include "hardmon/Utils.hpp"

#include <fstream>

namespace hardmon
{

void CGnuPlotFile::writeData(const std::string &fileName,
                             const std::vector<TSensorFrequency>& xValues,
                             const std::vector<TSensorValue>& yValues)
{
    if (xValues.size() != yValues.size()) {
        throw std::runtime_error("xValues has different size than yValues");
    }

    std::ofstream plotFile(fileName);
    if (!plotFile.is_open()) {
        throw std::runtime_error(string_format("cannot open file: %s", fileName.c_str()));
    }

    plotFile << "$data << EOD" << std::endl;

    for (size_t i = 0; i < xValues.size(); ++i) {
        plotFile << xValues[i] << " " << yValues[i] << std::endl;
    }

    plotFile << "EOD" << std::endl;
    plotFile << std::endl;

    if (m_title.size()) {
        plotFile << "set title '" << m_title << "'" << std::endl;
    }

    if (m_xLabel.size()) {
        plotFile << "set xlabel '" << m_xLabel << "'" << std::endl;
    }

    if (m_yLabel.size()) {
        plotFile << "set ylabel '" << m_yLabel << "'" << std::endl;
    }

    // plot section

    plotFile << "plot \"$data\" \\" << std::endl;

    if (m_linesPoints) {
        plotFile << "with linespoints \\" << std::endl;
    }

    if (m_title.size()) {
        plotFile << "title '" << m_title << "' \\" << std::endl;
    }

    plotFile << std::endl;
}

}

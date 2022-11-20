#pragma once

#include "hardmon/Types.hpp"

#include <vector>

#include <boost/filesystem.hpp>


namespace hardmon
{

class CFftAnalysis
{
public:
    CFftAnalysis();
    ~CFftAnalysis();

    // runs FFT on the specified data
    // NOTE: the implementation should be improved.
    void frequencyMagnitude(std::vector<TSensorValue>& out,
                            const std::vector<TSensorValue>& values,
                            size_t threads) const;

    // returns frequency for the specified index
    static TSensorFrequency frequencyIndex(TSensorFrequency frequencyHz, size_t index, size_t count) {
        return frequencyHz * index / count;
    }

private:
    boost::filesystem::path m_tmpDir;
    boost::filesystem::path m_wisdomPath;
};

}

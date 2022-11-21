#pragma once

#include "hardmon/Types.hpp"

#include <vector>

#include <boost/filesystem.hpp>

namespace hardmon {

/*!
 * \brief The CFftAnalysis class provides methods for Fast Fourier transformation.
 */
class CFftAnalysis
{
public:
    CFftAnalysis();
    ~CFftAnalysis();

    /*!
     * \brief Runs FFT on the specified data to obtain magnitutes for frequencies.
     * \param out the vector to store FFT result. It would be resized during FFT calculation.
     * \param values the input data for FFT.
     * \param threads the number of threads to use for FFT calculation.
     */
    void frequencyMagnitude(std::vector<TSensorValue>& out,
                            const std::vector<TSensorValue>& values,
                            size_t threads) const;

    /*!
     * \brief Calculates frequency corresponding to the specified \a index on X axis.
     * \param frequencyHz the frequency of the signal
     * \param index the position on X axes
     * \param count the total number of measured points (on X axes)
     * \return
     */
    static TSensorFrequency frequencyIndex(TSensorFrequency frequencyHz, size_t index, size_t count)
    {
        return frequencyHz * index / count;
    }

private:
    boost::filesystem::path m_tmpDir;
    boost::filesystem::path m_wisdomPath;
};

} // namespace hardmon

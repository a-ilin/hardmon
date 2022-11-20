#include "hardmon/CFftAnalysis.hpp"

#include <fftwpp/Array.h>
#include <fftwpp/fftw++.h>


namespace bf = boost::filesystem;

namespace hardmon
{

CFftAnalysis::CFftAnalysis()
{
    // Create temporary directory for FFTW wisdom file.

    m_tmpDir = bf::temp_directory_path() / bf::unique_path();
    bf::create_directories(m_tmpDir);

    m_wisdomPath = m_tmpDir / "fftw_wisdom.txt";

    fftwpp::fftw::WisdomName = m_wisdomPath.c_str();
}

CFftAnalysis::~CFftAnalysis()
{
    fftwpp::fftw::WisdomName = nullptr;

    bf::remove_all(m_tmpDir);
}

void CFftAnalysis::frequencyMagnitude(std::vector<TSensorValue> &out,
                                      const std::vector<TSensorValue> &values,
                                      size_t threads) const
{
    const size_t n = values.size();   // input size
    const size_t np = n/2+1;          // output size

    constexpr size_t align = sizeof(Complex);
    Array::array1<TSensorValue> fIn(n, align);
    Array::array1<Complex> fOut(np, align);

    // create FFT plan
    fftwpp::rcfft1d forward(n, fIn, fOut, threads);

    // NOTE: load data after creation of the plan!
    fIn.Load(values.data());

    // execute FFT plan
    forward.fft(fIn, fOut);

    // calculate power spectrum
    out.resize(np - 1);
    for (size_t i = 1; i < np; ++i) {
        TSensorValue mag = abs(fOut[i]);
        out[i-1] = mag;
    }
}


}

#include "hardmon/CFftAnalysis.hpp"
#include "hardmon/plotfile/CGnuPlotFile.hpp"
#include "hardmon/storage/CStorage.hpp"

#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Args
{
    std::string dataFileName;
    std::string sensor;
    std::string plotFileName;
    bool doFFT = false;
    size_t threads = 1;
};

static bool parseArgs(Args &args, int argc, char* argv[])
{
    po::options_description desc("Usage");
    desc.add_options()
        ("help", "produce help message")
        ("data", po::value<std::string>(), "path to input HDF5 file")
        ("sensor", po::value<std::string>(), "identifier of the sensor to draw")
        ("plot", po::value<std::string>(), "path to output gnuplot file")
        ("fft", "transform data with FFT")
        ("threads", po::value<size_t>(), "threads to use for FFT");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return false;
    }

    try {
        args.dataFileName = vm["data"].as<std::string>();
        args.sensor = vm["sensor"].as<std::string>();
        args.plotFileName = vm["plot"].as<std::string>();
        args.doFFT = vm.count("fft") > 0;

        if (vm.count("threads")) {
            args.threads = vm["threads"].as<size_t>();
        }
    } catch (const std::exception&) {
        std::cout << desc << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    using namespace hardmon;

    Args args;
    if (!parseArgs(args, argc, argv)) {
        return 1;
    }

    CGnuPlotFile gnuplot;
    gnuplot.setTitle(args.sensor);
    gnuplot.setXLabel(args.doFFT ? "Frequency" : "Time");
    gnuplot.setYLabel(args.doFFT ? "Magnitute" : "Value");
    gnuplot.setLinesPoints(true);

    auto storage = std::make_shared<CStorage>(args.dataFileName);
    storage->load(args.sensor);

    const auto& values = storage->values(args.sensor);
    const auto& attr = storage->sensorAttributes(args.sensor);

    if (args.doFFT) {
        std::vector<TSensorValue> fftResult;
        CFftAnalysis fftAnalysis;
        fftAnalysis.frequencyMagnitude(fftResult, values, args.threads);

        std::vector<TSensorFrequency> fftFreq;
        for (size_t i = 0; i < fftResult.size(); ++i) {
            fftFreq.push_back(CFftAnalysis::frequencyIndex(attr.freqHz, i, fftResult.size()));
        }

        gnuplot.writeData(args.plotFileName, fftFreq, fftResult);
    } else {
        std::vector<TSensorFrequency> runTime;
        for (size_t i = 0; i < values.size(); ++i) {
            runTime.push_back(static_cast<TSensorFrequency>(attr.interval.total_milliseconds()) / 1000 * i);
        }

        gnuplot.writeData(args.plotFileName, runTime, values);
    }

    return 0;
}

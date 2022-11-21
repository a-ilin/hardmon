#include "hardmon/CSensorReader.hpp"
#include "hardmon/CSignalHandler.hpp"
#include "hardmon/storage/CHdf5Storage.hpp"

#include <iostream>

#include <boost/program_options.hpp>

#include <yaml-cpp/yaml.h>

struct Args
{
    std::string configFileName;
    std::string dataFileName;
};

namespace po = boost::program_options;

static bool parseArgs(Args& args, int argc, char* argv[])
{
    po::options_description desc("Usage");
    // clang-format off
    desc.add_options()
        ("help", "produce help message")
        ("config", po::value<std::string>(), "path to config file")
        ("data", po::value<std::string>(), "path to output HDF5 file");
    // clang-format on

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return false;
    }

    try {
        if (vm.count("config")) {
            args.configFileName = vm["config"].as<std::string>();
        } else {
            args.configFileName = READER_CONFIG_FILE;
        }

        args.dataFileName = vm["data"].as<std::string>();
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
        // no need to print message here
        return 1;
    }

    YAML::Node config = YAML::LoadFile(args.configFileName);
    if (config.IsNull()) {
        throw std::runtime_error("Config file is empty");
    }

    auto storage = std::make_shared<CHdf5Storage>(args.dataFileName);

    CSensorReader reader(storage, config["threads"].as<size_t>());
    reader.configureSensors(config["sensors"]);

    reader.start();

    // run forever until signal received
    CSignalHandler signalHandler;
    signalHandler.wait();

    reader.stop();
    storage->saveAll();

    return 0;
}

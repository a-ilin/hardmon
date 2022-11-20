#include "hardmon/CSensorReader.hpp"
#include "hardmon/CSignalHandler.hpp"
#include "hardmon/storage/CStorage.hpp"

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
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("config", po::value<std::string>(), "path to config file")
        ("data", po::value<std::string>(), "path to output HDF5 file");

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
    } catch (const std::exception&) {
        std::cout << desc << std::endl;
        return false;
    }

    args.dataFileName = vm["data"].as<std::string>();

    return true;
}

int main(int argc, char* argv[])
{
    using namespace hardmon;

    Args args;
    if (!parseArgs(args, argc, argv)) {
        return 1;
    }

    YAML::Node config = YAML::LoadFile(args.configFileName);
    if (config.IsNull()) {
        return 1;
    }

    auto storage = std::make_shared<CStorage>(args.dataFileName);

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

#include "CLI.hpp"
#include "Info.hpp"

AssaultPlan CLIConfig::makeAssaultPlan() const {
    if (difficulty == "test") {
        return makeTestAssaultPlan();
    } else if (difficulty == "easy") {
        return makeEasyAssaultPlan();
    } else if (difficulty == "hard") {
        return makeHardAssaultPlan();
    } else if (difficulty == "extra-hard") {
        return makeExtraHardAssaultPlan();
    } else {
        return makeNormalAssaultPlan();
    }
}

LogLevel CLIConfig::getLogLevel() const {
    return static_cast<LogLevel>(logLevel);
}

int CLIConfig::getNumTunnels() const {
    if (difficulty == "test") {
        return 1;
    } else if (difficulty == "easy") {
        return 2;
    } else {
        return 4;
    }
}

void ConfigManager::setConfig(const CLIConfig &cfg) {
    config = cfg;
    initialized = true;
}

const CLIConfig &ConfigManager::getConfig() {
    if (!initialized) {
        throw std::runtime_error("Config not initialized");
    }
    return config;
}

CLI::CLI() : parser(ProjectInfo::PROJECT_NAME, ProjectInfo::VERSION) {
    parser.add_argument("-d", "--difficulty")
        .help("sets difficulty of game (test/easy/normal/hard/extra-hard)")
        .metavar("DIFFICULTY")
        .default_value(string("normal"))
        .choices("test", "easy", "normal", "hard", "extra-hard")
        .store_into(config.difficulty);

    parser.add_argument("-w", "--water")
        .help("loads a full layout with water")
        .flag()
        .store_into(config.waterEnabled);

    parser.add_argument("-f", "--food")
        .help("number of food to start with when testing")
        .metavar("FOOD")
        .default_value(2)
        .scan<'i', int>()
        .store_into(config.initialFood);

    parser.add_argument("-l", "--log")
        .help("sets log level (0:TEST, 1:INFO, 2:ERROR, 3:NONE)")
        .metavar("LEVEL")
        .default_value(1)
        .scan<'i', int>()
        .store_into(config.logLevel);
}

CLIConfig CLI::parse(int argc, char *argv[]) {
    try {
        parser.parse_args(argc, argv);
        return config;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        std::exit(1);
    }
}

CLIConfig CLI::getConfig() const {
    return config;
}
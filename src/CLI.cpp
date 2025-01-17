#include "CLI.hpp"
#include "Info.hpp"
#include <iostream>

void CLIConfig::loadFromJson(const json &j) {
    if (j.contains("difficulty")) {
        difficulty = j["difficulty"];
    }
    if (j.contains("water")) {
        waterEnabled = j["water"];
    }
    if (j.contains("autoOpen")) {
        autoOpen = j["autoOpen"];
    }
    if (j.contains("initialFood")) {
        initialFood = j["initialFood"];
    }
    if (j.contains("logLevel")) {
        logLevel = j["logLevel"];
    }
    if (j.contains("port")) {
        port = j["port"];
    }
}

void CLIConfig::saveToJson(const string &path) const {
    json j;
    j["difficulty"] = difficulty;
    j["water"] = waterEnabled;
    j["autoOpen"] = autoOpen;
    j["initialFood"] = initialFood;
    j["logLevel"] = logLevel;
    j["port"] = port;
    std::ofstream file(path);
    file << j.dump(2);
}

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
        THROW_EXCEPTION(std::runtime_error, "Config not initialized");
    }
    return config;
}

CLI::CLI() : parser(ProjectInfo::PROJECT_NAME, ProjectInfo::VERSION) {
    parser.add_argument("-d", "--difficulty")
        .help("sets difficulty of game (test/easy/normal/hard/extra-hard)")
        .metavar("DIFFICULTY")
        .default_value("normal")
        .choices("test", "easy", "normal", "hard", "extra-hard")
        .nargs(1)
        .action([this](const std::string &value) {
            if (parser.is_used("--difficulty")) {
                cmdConfig.difficulty = value;
            }
            return value;
        });

    parser.add_argument("-w", "--water")
        .help("loads a full layout with water")
        .flag()
        .action([this](const std::string &) {
            cmdConfig.waterEnabled = true;
            return "true";
        });

    parser.add_argument("-o", "--open")
        .help("automatically open the game in a browser (maybe not work in your OS!)")
        .flag()
        .action([this](const std::string &) {
            cmdConfig.autoOpen = true;
            return "true";
        });

    parser.add_argument("-f", "--food")
        .help("number of food to start with when testing")
        .metavar("FOOD")
        .default_value(2)
        .scan<'i', int>()
        .nargs(1)
        .action([this](const std::string &value) {
            cmdConfig.initialFood = std::stoi(value);
            return value;
        });

    parser.add_argument("-l", "--log")
        .help("sets log level (0:TEST, 1:INFO, 2:ERROR, 3:NONE)")
        .metavar("LEVEL")
        .default_value(1)
        .scan<'i', int>()
        .choices(0, 1, 2, 3)
        .nargs(1)
        .action([this](const std::string &value) {
            cmdConfig.logLevel = std::stoi(value);
            return value;
        });

    parser.add_argument("-p", "--port")
        .help("sets the port for the server")
        .metavar("PORT")
        .default_value(18080)
        .scan<'i', int>()
        .nargs(1)
        .action([this](const std::string &value) {
            cmdConfig.port = std::stoi(value);
            return value;
        });

    parser.add_argument("-c", "--config")
        .help("path to config file")
        .metavar("CONFIG")
        .default_value("./config.json")
        .nargs(1)
        .action([this](const std::string &value) {
            cmdConfig.configPath = value;
            return value;
        });

    parser.add_argument("-s", "--save")
        .help("save game configuration to file and exit")
        .metavar("SAVE")
        .flag();
}

void CLI::loadConfigFile(const string &path, CLIConfig &cfg) {
    try {
        std::ifstream file(path);
        if (file.is_open()) {
            json j;
            file >> j;
            cfg.loadFromJson(j);
        }
    } catch (const exception &e) {
        if (path != "./config.json") {
            log(LOGERROR, format("Failed to load config file {0}: {1}", path, e.what()));
        }
    }
}

CLIConfig CLI::parse(int argc, char *argv[]) {
    try {
        config = CLIConfig();
        loadConfigFile("./config.json", config);
        parser.parse_args(argc, argv);
        if (!cmdConfig.configPath.empty() && cmdConfig.configPath != "./config.json") {
            loadConfigFile(cmdConfig.configPath, config);
        }
        if (parser.is_used("--difficulty")) {
            config.difficulty = cmdConfig.difficulty;
        }
        if (parser.is_used("--water")) {
            config.waterEnabled = cmdConfig.waterEnabled;
        }
        if (parser.is_used("--open")) {
            config.autoOpen = cmdConfig.autoOpen;
        }
        if (parser.is_used("--food")) {
            config.initialFood = cmdConfig.initialFood;
        }
        if (parser.is_used("--log")) {
            config.logLevel = cmdConfig.logLevel;
        }
        if (parser.is_used("--port")) {
            config.port = cmdConfig.port;
        }
        ConfigManager::setConfig(config);
        if (parser["--save"] == true) {
            config.saveToJson("./config.json");
            log(LOGINFO, "Configuration saved to ./config.json");
            exit(0);
        }
        return config;
    } catch (const std::runtime_error &err) {
        log(LOGERROR, format("Error parsing CLI arguments: {0}", err.what()));
        std::cerr << parser << std::endl;
        exit(1);
    }
}

CLIConfig CLI::getConfig() const {
    return config;
}
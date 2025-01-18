#include "CLI.hpp"
#include "Info.hpp"
#include <iostream>

void CLIConfig::loadFromJson(const json &j) {
    if (j.contains("difficulty")) {
        difficulty = j["difficulty"];
    }
    if (j.contains("planPath")) {
        planPath = j["planPath"];
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
    j["planPath"] = planPath;
    j["water"] = waterEnabled;
    j["autoOpen"] = autoOpen;
    j["initialFood"] = initialFood;
    j["logLevel"] = logLevel;
    j["port"] = port;
    std::ofstream file(path);
    file << j.dump(2);
}

void CLIConfig::setCustomePlan(const AssaultPlan &plan) {
    customPlan = plan;
    hasCustomPlan = true;
}

AssaultPlan CLIConfig::getAssaultPlan() const {
    if (hasCustomPlan) {
        return customPlan;
    }
    if (!planPath.empty()) {
        try {
            std::ifstream file(planPath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open plan file");
            }
            json j;
            file >> j;
            return AssaultPlan::deserialize(j);
        } catch (const exception &e) {
            log(LOGERROR, format("Failed to load plan file {0}: {1}", planPath, e.what()), true);
        }
    }
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

CLI::CLI() : parser(AVSBInfo::PROJECT_NAME, AVSBInfo::VERSION) {
    auto &group = parser.add_mutually_exclusive_group();
    group.add_argument("-d", "--difficulty")
        .help("sets difficulty of game (test/easy/normal/hard/extra-hard)")
        .metavar("DIFFICULTY")
        .default_value("normal")
        .choices("test", "easy", "normal", "hard", "extra-hard")
        .nargs(1)
        .required()
        .store_into(cmdConfig.difficulty);
    group.add_argument("-a", "--plan")
        .help("path to custom assault plan JSON file")
        .metavar("PLAN")
        .nargs(1)
        .required()
        .store_into(cmdConfig.planPath);
    parser.add_argument("-w", "--water")
        .help("loads a full layout with water")
        .flag()
        .store_into(cmdConfig.waterEnabled);
    parser.add_argument("-o", "--open")
        .help("automatically open the game in a browser (maybe not work in your OS!)")
        .flag()
        .store_into(cmdConfig.autoOpen);
    parser.add_argument("-f", "--food")
        .help("number of food to start with when testing")
        .metavar("FOOD")
        .default_value(2)
        .scan<'i', int>()
        .nargs(1)
        .required()
        .store_into(cmdConfig.initialFood);
    parser.add_argument("-l", "--log")
        .help("sets log level (0:TEST, 1:INFO, 2:ERROR, 3:NONE)")
        .metavar("LEVEL")
        .default_value(1)
        .scan<'i', int>()
        .choices(0, 1, 2, 3)
        .nargs(1)
        .required()
        .store_into(cmdConfig.logLevel);
    parser.add_argument("-p", "--port")
        .help("sets the port for the server")
        .metavar("PORT")
        .default_value(18080)
        .scan<'i', int>()
        .nargs(1)
        .required()
        .store_into(cmdConfig.port);
    parser.add_argument("-c", "--config")
        .help("path to config file")
        .metavar("CONFIG")
        .default_value("./config.json")
        .nargs(1)
        .required()
        .store_into(cmdConfig.configPath);
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
            log(LOGERROR, format("Failed to load config file {0}: {1}", path, e.what()), true);
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
        if (parser.is_used("--plan")) {
            config.planPath = cmdConfig.planPath;
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
    } catch (const exception &err) {
        log(LOGERROR, format("Error parsing CLI arguments: {0}", err.what()), true);
        std::cerr << parser;
        exit(1);
    }
}

CLIConfig CLI::getConfig() const {
    return config;
}
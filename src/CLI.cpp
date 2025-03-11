#include "CLI.hpp"
#include "ProjectVersion.hpp"
#include <iostream>

#define LOAD_JSON(name)      \
    if (j.contains(#name)) { \
        name = j[#name];     \
    }

#define STORE_JSON(name) j[#name] = name;

void CLIConfig::loadFromJson(const json &j) {
    LOAD_JSON(difficulty)
    LOAD_JSON(planPath)
    LOAD_JSON(waterEnabled)
    LOAD_JSON(autoOpen)
    LOAD_JSON(initialFood)
    LOAD_JSON(logLevel)
    LOAD_JSON(port)
}

void CLIConfig::saveToJson(const string &path) const {
    json j;
    STORE_JSON(difficulty)
    STORE_JSON(planPath)
    STORE_JSON(waterEnabled)
    STORE_JSON(autoOpen)
    STORE_JSON(initialFood)
    STORE_JSON(logLevel)
    STORE_JSON(port)
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

CLI::CLI() : parser(AVSBInfo::PROJECT_NAME, FULL_VERSION) {
    // [ISSUE] `store_into` is incompatible with `required`
    // https://github.com/p-ranav/argparse/issues/385)
    // temporary workaround: remove `required()`.
    auto &group = parser.add_mutually_exclusive_group();
    group.add_argument("-d", "--difficulty")
        .default_value("normal")
        .help("sets difficulty of game (test/easy/normal/hard/extra-hard)")
        .metavar("DIFFICULTY")
        .choices("test", "easy", "normal", "hard", "extra-hard")
        .nargs(1)
        .store_into(cmdConfig.difficulty);
    group.add_argument("-a", "--plan")
        .help("path to custom assault plan JSON file")
        .metavar("PLAN")
        .nargs(1)
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
        .default_value(2)
        .help("number of food to start with when testing")
        .metavar("FOOD")
        .scan<'i', int>()
        .nargs(1)
        .store_into(cmdConfig.initialFood);
    parser.add_argument("-l", "--log")
        .default_value(1)
        .help("sets log level (0:TEST, 1:INFO, 2:ERROR, 3:NONE)")
        .metavar("LEVEL")
        .scan<'i', int>()
        .choices(0, 1, 2, 3)
        .nargs(1)
        .store_into(cmdConfig.logLevel);
    parser.add_argument("-p", "--port")
        .default_value(18080)
        .help("sets the port for the server")
        .metavar("PORT")
        .scan<'i', int>()
        .nargs(1)
        .store_into(cmdConfig.port);
    parser.add_argument("-c", "--config")
        .default_value("./config.json")
        .help("path to config file")
        .metavar("CONFIG")
        .nargs(1)
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

#define UPDATE_CLI_CONFIG(option, name) \
    if (parser.is_used("--" #option)) { \
        config.name = cmdConfig.name;   \
    }

CLIConfig CLI::parse(int argc, char *argv[]) {
    try {
        config = CLIConfig();
        loadConfigFile("./config.json", config);
        parser.parse_args(argc, argv);
        if (!cmdConfig.configPath.empty() && cmdConfig.configPath != "./config.json") {
            loadConfigFile(cmdConfig.configPath, config);
        }
        UPDATE_CLI_CONFIG(difficulty, difficulty)
        UPDATE_CLI_CONFIG(plan, planPath)
        UPDATE_CLI_CONFIG(water, waterEnabled)
        UPDATE_CLI_CONFIG(open, autoOpen)
        UPDATE_CLI_CONFIG(food, initialFood)
        UPDATE_CLI_CONFIG(log, logLevel)
        UPDATE_CLI_CONFIG(port, port)
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
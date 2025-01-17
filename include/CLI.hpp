#ifndef CLI_HPP
#define CLI_HPP

#include "MakePlans.hpp"

class CLIConfig {
private:
    string difficulty = "normal";
    bool waterEnabled = false;
    bool autoOpen = false;
    int initialFood = 2;
    int logLevel = 1;
    int port = 18080;
    string configPath = "./config.json";
    string planPath = "";

    AssaultPlan customPlan;
    bool hasCustomPlan = false;

    friend class CLI;
    friend class Server;
    friend GameState createGameState(const CLIConfig &config);

public:
    void loadFromJson(const json &j);

    void saveToJson(const string &path) const;

    void setCustomePlan(const AssaultPlan &plan);

    [[nodiscard]]
    AssaultPlan getAssaultPlan() const;

    [[nodiscard]]
    LogLevel getLogLevel() const;

    int getNumTunnels() const;
};

class ConfigManager {
private:
    static inline CLIConfig config;
    static inline bool initialized = false;

public:
    static void setConfig(const CLIConfig &cfg);

    static const CLIConfig &getConfig();
};

class CLI {
private:
    argparse::ArgumentParser parser;
    CLIConfig config;
    CLIConfig cmdConfig;

public:
    CLI();

    void loadConfigFile(const string &path, CLIConfig &cfg);

    [[nodiscard]]
    CLIConfig parse(int argc, char *argv[]);

    [[nodiscard]]
    CLIConfig getConfig() const;
};

#endif // CLI_HPP
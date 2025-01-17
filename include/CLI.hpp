#ifndef CLI_HPP
#define CLI_HPP

#include "MakePlans.hpp"

struct CLIConfig {
    string difficulty = "normal";
    bool waterEnabled = false;
    int initialFood = 2;
    int logLevel = 1;
    int port = 18080;
    string configPath = "./config.json";

    friend class CLI;

    void loadFromJson(const json &j);

    void saveToJson(const string &path) const;

    AssaultPlan makeAssaultPlan() const;

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
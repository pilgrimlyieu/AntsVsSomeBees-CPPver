#ifndef CLI_HPP
#define CLI_HPP

#include "MakePlans.hpp"

struct CLIConfig {
    string difficulty;
    bool waterEnabled;
    int initialFood;
    int logLevel;

    friend class CLI;

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

public:
    CLI();

    [[nodiscard]]
    CLIConfig parse(int argc, char *argv[]);

    [[nodiscard]]
    CLIConfig getConfig() const;
};

#endif // CLI_HPP
#ifndef CLI_HPP
#define CLI_HPP

#include "MakePlans.hpp"

#include <argparse/argparse.hpp>

struct CLIConfig {
    string difficulty = "normal";
    bool waterEnabled;
    int initialFood;

    AssaultPlan makeAssaultPlan() const {
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

    int getNumTunnels() const {
        if (difficulty == "test") {
            return 1;
        } else if (difficulty == "easy") {
            return 2;
        } else {
            return 4;
        }
    }
};

class CLI {
private:
    argparse::ArgumentParser parser;
    CLIConfig config;

public:
    CLI();

    [[nodiscard]]
    CLIConfig parse(int argc, char *argv[]);
};

#endif // CLI_HPP
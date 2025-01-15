#ifndef MAKEPLANS_HPP
#define MAKEPLANS_HPP

#include "AssaultPlan.hpp"

AssaultPlan makeTestAssaultPlan();

AssaultPlan makeEasyAssaultPlan();

AssaultPlan makeNormalAssaultPlan();

AssaultPlan makeHardAssaultPlan();

AssaultPlan makeExtraHardAssaultPlan();

GameState createGameState(const CLIConfig &config);

#endif
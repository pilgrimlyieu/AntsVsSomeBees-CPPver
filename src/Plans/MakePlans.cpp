#include "MakePlans.hpp"
#include "Boss.hpp"
#include "CLI.hpp"
#include "GameState.hpp"
#include "Hive.hpp"
#include "Hornet.hpp"
#include "NinjaBee.hpp"
#include "Wasp.hpp"

#define CREATE_BEES(type) [](double health) { return new type(health); }

AssaultPlan makeTestAssaultPlan() {
    AssaultPlan plan = AssaultPlan();
    plan.addWave(CREATE_BEES(Bee), 3.0, 2, 1);
    plan.addWave(CREATE_BEES(Bee), 3.0, 3, 1);
    return plan;
}

AssaultPlan makeEasyAssaultPlan() {
    AssaultPlan plan = AssaultPlan();
    for (int time = 3; time < 16; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 3.0, time, 1);
    }
    plan.addWave(CREATE_BEES(Wasp), 3.0, 4, 1);
    plan.addWave(CREATE_BEES(NinjaBee), 3.0, 8, 1);
    plan.addWave(CREATE_BEES(Hornet), 3.0, 12, 1);
    plan.addWave(CREATE_BEES(Boss), 15.0, 16, 1);
    return plan;
}

AssaultPlan makeNormalAssaultPlan() {
    AssaultPlan plan = AssaultPlan();
    for (g_time time = 3; time < 16; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 3.0, time, 2);
    }
    plan.addWave(CREATE_BEES(Wasp), 3.0, 4, 1);
    plan.addWave(CREATE_BEES(NinjaBee), 3.0, 8, 1);
    plan.addWave(CREATE_BEES(Hornet), 3.0, 12, 1);
    plan.addWave(CREATE_BEES(Wasp), 3.0, 16, 1);

    // Boss Stage
    for (g_time time = 21; time < 30; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 3.0, time, 2);
    }
    plan.addWave(CREATE_BEES(Wasp), 3.0, 22, 2);
    plan.addWave(CREATE_BEES(Hornet), 3.0, 24, 2);
    plan.addWave(CREATE_BEES(NinjaBee), 3.0, 26, 2);
    plan.addWave(CREATE_BEES(Hornet), 3.0, 28, 2);
    plan.addWave(CREATE_BEES(Boss), 20.0, 30, 1);
    return plan;
}

AssaultPlan makeHardAssaultPlan() {
    AssaultPlan plan = AssaultPlan();
    for (g_time time = 3; time < 16; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 4.0, time, 2);
    }
    plan.addWave(CREATE_BEES(Wasp), 4.0, 4, 2);
    plan.addWave(CREATE_BEES(NinjaBee), 4.0, 8, 2);
    plan.addWave(CREATE_BEES(Hornet), 4.0, 12, 2);
    plan.addWave(CREATE_BEES(Wasp), 4.0, 16, 2);

    // Boss Stage
    for (g_time time = 21; time < 30; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 4.0, time, 3);
    }
    plan.addWave(CREATE_BEES(Wasp), 4.0, 22, 2);
    plan.addWave(CREATE_BEES(Hornet), 4.0, 24, 2);
    plan.addWave(CREATE_BEES(NinjaBee), 4.0, 26, 2);
    plan.addWave(CREATE_BEES(Hornet), 4.0, 28, 2);
    plan.addWave(CREATE_BEES(Boss), 30.0, 30, 1);
    return plan;
}

AssaultPlan makeExtraHardAssaultPlan() {
    AssaultPlan plan = AssaultPlan();
    plan.addWave(CREATE_BEES(Hornet), 5.0, 2, 2);
    for (g_time time = 3; time < 16; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 5.0, time, 2);
    }
    plan.addWave(CREATE_BEES(Wasp), 5.0, 4, 2);
    plan.addWave(CREATE_BEES(NinjaBee), 5.0, 8, 2);
    plan.addWave(CREATE_BEES(Hornet), 5.0, 12, 2);
    plan.addWave(CREATE_BEES(Wasp), 5.0, 16, 2);

    // Boss Stage
    for (g_time time = 21; time < 30; time += 2) {
        plan.addWave(CREATE_BEES(Bee), 5.0, time, 3);
    }
    plan.addWave(CREATE_BEES(Wasp), 5.0, 22, 2);
    plan.addWave(CREATE_BEES(Hornet), 5.0, 24, 2);
    plan.addWave(CREATE_BEES(NinjaBee), 5.0, 26, 2);
    plan.addWave(CREATE_BEES(Hornet), 5.0, 28, 2);
    plan.addWave(CREATE_BEES(Boss), 30.0, 30, 2);
    return plan;
}

GameState createGameState(const CLIConfig &config) {
    AssaultPlan plan = config.makeAssaultPlan();
    Hive *beehive = new Hive(&plan);
    static const int tunnelLength = 10;
    dim dimensions = {config.getNumTunnels(), tunnelLength};
    return GameState(beehive, config.waterEnabled ? wetLayout : dryLayout, dimensions,
                     config.initialFood);
}
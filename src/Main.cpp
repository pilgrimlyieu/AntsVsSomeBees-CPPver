#include "AntFactory.h"
#include "AntRemover.h"
#include "FireAnt.h"
#include "GameState.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        strat strategy = [](GameState &gameState) {
            // TODO
        };
        AntFactory *antFactory = &AntFactory::getInstance();
        Hive *beehive = new Hive(new AssaultPlan());
        auto register_place = [](Place *place, bool isBeeEntrance) {
            // TODO
        };
        auto createPlaces = [](AntHomeBase *base, auto registerPlace, dim dimensions) {
            // TODO
        };
        dim dimensions = {1, 1};
        GameState *gameState =
            new GameState(strategy, antFactory, beehive, createPlaces, dimensions, 100);
        std::cout << "Deploying ants" << std::endl;
    } catch (...) {
        log(LOGERROR, "An exception has occurred");
    }
    return 0;
}
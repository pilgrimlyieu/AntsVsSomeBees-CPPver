#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Utilities.h"

class GameState {
public:
    g_time time = 0;
    int food = 0;
    // strategy;
    Place *beehive;
    // antTypes;
    // dimensions;
    list<Bee *> activeBees = {};
    Ant *Queen; // TODO: Change to Queen
    // this.configure // TODO: Implement
};

#endif // GAMESTATE_H
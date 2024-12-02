#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "QueenAnt.h"
#include "Utilities.h"

class GameState {
public:
    g_time time = TIME_START;
    int food = 0;
    // strategy;
    Place *beehive;
    // antTypes;
    // dimensions;
    list<Bee *> activeBees = {};
    QueenAnt *Queen = nullptr;
    // this.configure // TODO: Implement
};

#endif // GAMESTATE_H
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "QueenAnt.h"
#include "Utilities.h"

class GameState final {
public:
    g_time time = TIME_START;
    int food = 0;
    // strategy;
    Place *beehive;
    // antTypes;
    // dimensions;
    std::list<Bee *> activeBees = {};
    QueenAnt *Queen = nullptr;
    // this.configure // TODO: Implement
};

void antsWin();

void antsLose();

#endif // GAMESTATE_H
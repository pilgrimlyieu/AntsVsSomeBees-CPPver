#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.h"

class HungryAnt : Ant {
public:
    string name = "Hungry";        // the name of the HungryAnt
    static const int foodCost = 4; // the food cost of the HungryAnt
    g_time chewDuration = 3;       // the duration of the HungryAnt's chewing
    g_time chewCountDown;          // the countdown for the HungryAnt's chewing

    HungryAnt(int health = 1);

    void action(GameState &gamestate);
};

#endif // HUNGRYANT_H
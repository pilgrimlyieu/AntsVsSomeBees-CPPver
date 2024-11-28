#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.h"

class HungryAnt : Ant {
  public:
    string name = "Hungry";
    static const int foodCost = 4;
    g_time chewDuration = 3;
    g_time chewCountDown;

    HungryAnt(int health = 1);

    void action(GameState &gamestate);
};

#endif // HUNGRYANT_H
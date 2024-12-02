#ifndef THROWERANT_H
#define THROWERANT_H

#include "Ant.h"

class ThrowerAnt : public Ant {
protected:
    Bee *nearestBee();
    void throwAt(Bee *target);

public:
    string name = "Thrower";       // the name of the Ant
    int damage = 1;                // the damage of the Ant
    static const int foodCost = 3; // the food cost of the Ant
    int minRange = 0;              // the minimum range of the Ant
    int maxRange = INT_MAX;        // the maximum range of the Ant

    void action(GameState &gamestate);
};

#endif // THROWERANT_H
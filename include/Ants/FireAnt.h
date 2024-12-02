#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt : public Ant {
public:
    string name = "Fire"; // the name of the FireAnt
    int damage = 3;       // the damage dealt by the FireAnt
    int foodCost = 5;     // the food cost of the FireAnt

    void reduceHealth(int amount);
};

#endif // FIREANT_H
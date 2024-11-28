#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt : public Ant {
    string name = "Fire";
    int damage = 3;
    int foodCost = 5;

    void reduceHealth(int amount);
};

#endif // FIREANT_H
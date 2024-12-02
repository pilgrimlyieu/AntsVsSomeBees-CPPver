#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.h"

class NinjaAnt : public Ant {
public:
    string name = "Ninja";               // the name of the Ant
    static const int foodCost = 5;       // the food cost of the Ant
    static const int damage = 1;         // the damage of the Ant
    static const bool blocksPath = true; // if the Ant can block the path

    void action(GameState &gamestate) override;
};

#endif // NINJAANT_H
#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.h"

class TankAnt : ContainerAnt {
public:
    string name = "Tank";          // the name of the Ant
    static const int foodCost = 6; // the food cost of the Ant
    static const int damage = 1;   // the damage of the Ant

    TankAnt(int health = 2);

    void action(GameState &gamestate) override;
};

#endif // TANKANT_H
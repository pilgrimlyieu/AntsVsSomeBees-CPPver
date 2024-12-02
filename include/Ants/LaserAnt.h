#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt : public ThrowerAnt {
    int insectsShot = 0; // the number of insects shot by the LaserAnt

    unordered_map<Insect *, int> getTargets();
    int getDamage(int distance);

public:
    string name = "Laser";          // the name of the Ant
    static const int foodCost = 10; // the food cost of the Ant
    static const int damage = 2;    // the damage of the Ant

    void action(GameState &gamestate) override;
};

#endif // LASERANT_H
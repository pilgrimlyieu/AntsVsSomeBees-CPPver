#ifndef WALLANT_H
#define WALLANT_H

#include "Ant.h"

class WallAnt : public Ant {
public:
    string name = "Wall";          // the name of the Ant
    static const int foodCost = 4; // the food cost of the Ant

    WallAnt(int health = 4);
};

#endif // WALLANT_H
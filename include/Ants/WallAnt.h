#ifndef WALLANT_H
#define WALLANT_H

#include "Ant.h"

class WallAnt : public Ant {
  public:
    string name = "Wall";
    static const int foodCost = 4;

    WallAnt(int health = 4);
};

#endif // WALLANT_H
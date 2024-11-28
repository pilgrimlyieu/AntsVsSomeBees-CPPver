#ifndef THROWERANT_H
#define THROWERANT_H

#include "Ant.h"

class ThrowerAnt : public Ant {
  protected:
    Bee *nearestBee();
    void throwAt(Bee *target);

  public:
    string name = "Thrower";
    int damage = 1;
    static const int foodCost = 3;
    int minRange = 0;
    int maxRange = INT_MAX;

    void action(GameState &gamestate);
};

#endif // THROWERANT_H
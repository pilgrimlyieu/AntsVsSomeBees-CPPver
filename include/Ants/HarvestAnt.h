#ifndef HARVESTANT_H
#define HARVESTANT_H

#include "Ant.h"

class HarvestAnt : public Ant {
  public:
    string name = "Harvester";
    static const int foodCost = 2;

    void action(GameState &gamestate);
};

#endif // HARVESTANT_H
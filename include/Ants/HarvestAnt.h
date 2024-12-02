#ifndef HARVESTANT_H
#define HARVESTANT_H

#include "Ant.h"

class HarvestAnt : public Ant {
public:
    string name = "Harvester";     // the name of the HarvestAnt
    static const int foodCost = 2; // the food cost of the HarvestAnt

    void action(GameState &gamestate);
};

#endif // HARVESTANT_H
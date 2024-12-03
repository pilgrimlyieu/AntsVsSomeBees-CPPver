#ifndef HARVESTANT_H
#define HARVESTANT_H

#include "Ant.h"

class HarvestAnt : public Ant {
public:
    inline static const string name = "Harvester"; //!< 类名
    static const int foodCost = 2;                 //!< 食物消耗

    void action(GameState &gamestate);
};

#endif // HARVESTANT_H
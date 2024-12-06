#ifndef HARVESTANT_H
#define HARVESTANT_H

#include "Ant.h"

class HarvestAnt final : public Ant {
private:
    inline static const std::string name = "Harvester"; //!< 类名
    static const int foodCost = 2;                      //!< 食物消耗

public:
    void action(GameState &gamestate) override;
};

#endif // HARVESTANT_H
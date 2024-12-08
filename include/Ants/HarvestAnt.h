#ifndef HARVESTANT_H
#define HARVESTANT_H

#include "Ant.h"

class HarvestAnt final : public Ant {
public:
    explicit HarvestAnt(double health = 1.0);

    void action(GameState &gamestate) override final;
};

#endif // HARVESTANT_H
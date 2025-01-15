#ifndef HARVESTANT_HPP
#define HARVESTANT_HPP

#include "Ant.hpp"

class HarvestAnt final : public Ant {
public:
    explicit HarvestAnt(double health);

    explicit HarvestAnt() : HarvestAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // HARVESTANT_HPP
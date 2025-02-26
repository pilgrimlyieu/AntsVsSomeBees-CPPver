#ifndef HARVESTANT_HPP
#define HARVESTANT_HPP

#include "Ant.hpp"

class HarvestAnt final : public Ant {
protected:
    [[nodiscard]]
    string getName() const final {
        return "HarvestAnt";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 2;
    }

public:
    explicit HarvestAnt(double health) : Ant(health) {}
    explicit HarvestAnt() : HarvestAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // HARVESTANT_HPP
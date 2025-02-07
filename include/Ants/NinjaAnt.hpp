#ifndef NINJAANT_HPP
#define NINJAANT_HPP

#include "Ant.hpp"

class NinjaAnt final : public Ant {
protected:
    [[nodiscard]]
    string getName() const final {
        return "NinjaAnt";
    }
    [[nodiscard]]
    double getDefaultDamage() const final {
        return 1.0;
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 5;
    }
    [[nodiscard]]
    bool getBlocksPath() const final {
        return false;
    }

public:
    explicit NinjaAnt(double health) : Ant(health) {}
    explicit NinjaAnt() : NinjaAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // NINJAANT_HPP
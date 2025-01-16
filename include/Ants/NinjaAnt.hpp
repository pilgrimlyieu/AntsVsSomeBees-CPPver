#ifndef NINJAANT_HPP
#define NINJAANT_HPP

#include "Ant.hpp"

class NinjaAnt final : public Ant {
private:
    string getName() const final {
        return "NinjaAnt";
    }
    double getDefaultDamage() const final {
        return 1.0;
    }
    int getFoodCost() const final {
        return 5;
    }
    bool getBlocksPath() const final {
        return false;
    }

public:
    explicit NinjaAnt(double health) : Ant(health) {}
    explicit NinjaAnt() : NinjaAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // NINJAANT_HPP
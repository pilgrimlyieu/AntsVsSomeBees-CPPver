#ifndef TANKANT_HPP
#define TANKANT_HPP

#include "ContainerAnt.hpp"

class TankAnt final : public ContainerAnt {
protected:
    [[nodiscard]]
    string getName() const final {
        return "TankAnt";
    }
    [[nodiscard]]
    double getDefaultDamage() const final {
        return 1.0;
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 6;
    }

public:
    explicit TankAnt(double health) : ContainerAnt(health) {}
    explicit TankAnt() : TankAnt(2.0) {}

    void action(GameState &gamestate) final;
};

#endif // TANKANT_HPP
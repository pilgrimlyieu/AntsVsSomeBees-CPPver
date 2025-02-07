#ifndef FIREANT_HPP
#define FIREANT_HPP

#include "Ant.hpp"

class FireAnt final : public Ant {
protected:
    [[nodiscard]]
    string getName() const final {
        return "FireAnt";
    }
    [[nodiscard]]
    double getDefaultDamage() const final {
        return 3.0;
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 5;
    }

public:
    explicit FireAnt(double health) : Ant(health) {}
    explicit FireAnt() : FireAnt(3.0) {}

    void reduceHealth(double amount) final;
};

#endif // FIREANT_HPP
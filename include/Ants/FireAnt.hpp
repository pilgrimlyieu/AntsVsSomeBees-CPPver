#ifndef FIREANT_HPP
#define FIREANT_HPP

#include "Ant.hpp"

class FireAnt final : public Ant {
protected:
    string getName() const final {
        return "FireAnt";
    }
    double getDefaultDamage() const final {
        return 3.0;
    }
    int getFoodCost() const final {
        return 5;
    }

public:
    explicit FireAnt(double health) : Ant(health) {}
    explicit FireAnt() : FireAnt(3.0) {}

    void reduceHealth(double amount) final;
};

#endif // FIREANT_HPP
#ifndef SCARYTHROWER_HPP
#define SCARYTHROWER_HPP

#include "ThrowerAnt.hpp"

class ScaryThrower final : public ThrowerAnt {
private:
    string getName() const final {
        return "ScaryThrower";
    }
    int getFoodCost() const final {
        return 6;
    }

    void throwAt(Bee *target) final;

public:
    explicit ScaryThrower(double health) : ThrowerAnt(health) {}
    explicit ScaryThrower() : ScaryThrower(1.0) {}
};

#endif // SCARYTHROWER_HPP
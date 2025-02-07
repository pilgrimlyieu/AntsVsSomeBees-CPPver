#ifndef SCARYTHROWER_HPP
#define SCARYTHROWER_HPP

#include "ThrowerAnt.hpp"

class ScaryThrower final : public ThrowerAnt {
protected:
    [[nodiscard]]
    string getName() const final {
        return "ScaryThrower";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 6;
    }

    void throwAt(Bee *target) final;

public:
    explicit ScaryThrower(double health) : ThrowerAnt(health) {}
    explicit ScaryThrower() : ScaryThrower(1.0) {}
};

#endif // SCARYTHROWER_HPP
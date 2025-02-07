#ifndef SCUBATHROWER_HPP
#define SCUBATHROWER_HPP

#include "ThrowerAnt.hpp"

class ScubaThrower : public ThrowerAnt {
protected:
    [[nodiscard]]
    string getName() const override {
        return "ScubaThrower";
    }
    [[nodiscard]]
    int getFoodCost() const override {
        return 6;
    }
    [[nodiscard]]
    bool getIsWaterProof() const final {
        return true;
    }

public:
    explicit ScubaThrower(double health) : ThrowerAnt(health) {}
    explicit ScubaThrower() : ScubaThrower(1.0) {}
};

#endif // SCUBATHROWER_HPP
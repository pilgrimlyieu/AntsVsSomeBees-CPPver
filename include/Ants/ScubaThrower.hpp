#ifndef SCUBATHROWER_HPP
#define SCUBATHROWER_HPP

#include "ThrowerAnt.hpp"

class ScubaThrower : public ThrowerAnt {
protected:
    virtual string getName() const override {
        return "ScubaThrower";
    }
    virtual int getFoodCost() const override {
        return 6;
    }
    bool getIsWaterProof() const final {
        return true;
    }

public:
    explicit ScubaThrower(double health) : ThrowerAnt(health) {}
    explicit ScubaThrower() : ScubaThrower(1.0) {}
};

#endif // SCUBATHROWER_HPP
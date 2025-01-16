#ifndef THROWERANT_HPP
#define THROWERANT_HPP

#include "Ant.hpp"

class ThrowerAnt : public Ant {
protected:
    virtual string getName() const override {
        return "ThrowerAnt";
    }
    virtual double getDefaultDamage() const override {
        return 1.0;
    }
    virtual int getFoodCost() const override {
        return 3;
    }
    virtual int getMinRange() const {
        return 0;
    }
    virtual int getMaxRange() const {
        return INT_MAX;
    }

    const int minRange; //!< 最小射程
    const int maxRange; //!< 最大射程

    Bee *nearestBee();

    virtual void throwAt(Bee *target);

public:
    explicit ThrowerAnt(double health)
        : Ant(health), minRange(getMinRange()), maxRange(getMaxRange()) {}
    explicit ThrowerAnt() : ThrowerAnt(1.0) {}

    void action(GameState &gamestate) override;
};

#endif // THROWERANT_HPP
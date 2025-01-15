#ifndef THROWERANT_HPP
#define THROWERANT_HPP

#include "Ant.hpp"

class ThrowerAnt : public Ant {
protected:
    struct thrower_ant_properties : ant_properties {
        string name = "ThrowerAnt"; //!< 类名
        double damage = 1.0;        //!< 伤害
        int foodCost = 3;           //!< 食物消耗
        int minRange = 0;           //!< 最小射程
        int maxRange = INT_MAX;     //!< 最大射程
    };

    const int minRange; //!< 最小射程
    const int maxRange; //!< 最大射程

    Bee *nearestBee();

    virtual void throwAt(Bee *target);

public:
    explicit ThrowerAnt(double health, thrower_ant_properties properties);

    explicit ThrowerAnt(double health) : ThrowerAnt(health, {}) {}

    explicit ThrowerAnt() : ThrowerAnt(1.0) {}

    void action(GameState &gamestate) override;
};

#endif // THROWERANT_HPP
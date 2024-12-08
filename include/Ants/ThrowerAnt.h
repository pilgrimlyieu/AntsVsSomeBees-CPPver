#ifndef THROWERANT_H
#define THROWERANT_H

#include "Ant.h"

struct thrower_ant_properties : ant_properties {
    std::string name = "Thrower"; //!< 类名
    double damage = 1.0;          //!< 伤害
    int foodCost = 3;             //!< 食物消耗
    int minRange = 0;             //!< 最小射程
    int maxRange = INT_MAX;       //!< 最大射程
};

class ThrowerAnt : public Ant {
protected:
    const int minRange; //!< 最小射程
    const int maxRange; //!< 最大射程

    Bee *nearestBee();

    virtual void throwAt(Bee *target);

public:
    explicit ThrowerAnt(double health = 1.0, thrower_ant_properties properties = {});

    void action(GameState &gamestate) override;
};

#endif // THROWERANT_H
#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt final : public ThrowerAnt {
private:
    inline static const std::string name = "Laser"; //!< 类名
    static const int foodCost = 10;                 //!< 食物消耗
    double damage = 2.0;                            //!< 伤害
    int insectsShot = 0;                            //!< 射击的昆虫数量

    std::unordered_map<Insect *, int> getTargets();

    double getDamage(int distance);

public:
    void action(GameState &gamestate) override final;
};

#endif // LASERANT_H
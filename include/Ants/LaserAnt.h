#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt : public ThrowerAnt {
private:
    int insectsShot = 0; //!< 射击的昆虫数量

    unordered_map<Insect *, int> getTargets();
    int getDamage(int distance);

public:
    inline static const string name = "Laser"; //!< 类名
    static const int foodCost = 10;            //!< 食物消耗
    static const int damage = 2;               //!< 伤害

    void action(GameState &gamestate) override;
};

#endif // LASERANT_H
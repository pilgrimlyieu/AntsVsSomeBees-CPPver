#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.h"

class NinjaAnt : public Ant {
public:
    inline static const string name = "Ninja"; //!< 类名
    static const int foodCost = 5;             //!< 食物消耗
    static const int damage = 1;               //!< 伤害
    static const bool blocksPath = false;      //!< 是否阻挡路径

    void action(GameState &gamestate) override;
};

#endif // NINJAANT_H
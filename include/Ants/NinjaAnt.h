#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.h"

class NinjaAnt final : public Ant {
private:
    inline static const std::string name = "Ninja"; //!< 类名
    static const int foodCost = 5;                  //!< 食物消耗
    double damage = 1.0;                            //!< 伤害

public:
    static const bool blocksPath = false; //!< 是否阻挡路径

    void action(GameState &gamestate) override final;
};

#endif // NINJAANT_H
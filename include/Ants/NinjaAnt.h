#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.h"

class NinjaAnt final : public Ant {
private:
    inline static const std::string name = "Ninja"; //!< 类名
    static const int foodCost = 5;                  //!< 食物消耗
    int damage = 1;                                 //!< 伤害

public:
    static const bool blocksPath = false; //!< 是否阻挡路径

    void action(GameState &gamestate) override;
};

#endif // NINJAANT_H
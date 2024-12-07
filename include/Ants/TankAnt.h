#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.h"

class TankAnt final : public ContainerAnt {
private:
    inline static const std::string name = "Tank"; //!< 类名
    static const int foodCost = 6;                 //!< 食物消耗
    double damage = 1.0;                           //!< 伤害

public:
    explicit TankAnt(double health = 2.0);

    void action(GameState &gamestate) override final;
};

#endif // TANKANT_H
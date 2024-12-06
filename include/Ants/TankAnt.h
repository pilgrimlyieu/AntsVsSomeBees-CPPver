#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.h"

class TankAnt final : public ContainerAnt {
private:
    inline static const std::string name = "Tank"; //!< 类名
    static const int foodCost = 6;                 //!< 食物消耗
    int damage = 1;                                //!< 伤害

public:
    explicit TankAnt(int health = 2);

    void action(GameState &gamestate) override;
};

#endif // TANKANT_H
#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.h"

class TankAnt : public ContainerAnt {
public:
    inline static const string name = "Tank"; //!< 类名
    static const int foodCost = 6;            //!< 食物消耗
    static const int damage = 1;              //!< 伤害

    TankAnt(int health = 2);

    void action(GameState &gamestate);
};

#endif // TANKANT_H
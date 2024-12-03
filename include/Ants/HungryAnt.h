#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.h"

class HungryAnt : public Ant {
public:
    inline static const string name = "Hungry"; //!< 类名
    static const int foodCost = 4;              //!< 食物消耗
    static const g_time chewDuration = 3;       //!< 咀嚼持续时间
    g_time chewCountDown = 0;                   //!< 咀嚼倒计时

    HungryAnt(int health = 1);

    void action(GameState &gamestate);
};

#endif // HUNGRYANT_H
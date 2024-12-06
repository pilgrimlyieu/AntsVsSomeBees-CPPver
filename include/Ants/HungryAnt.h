#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.h"

class HungryAnt final : public Ant {
private:
    inline static const std::string name = "Hungry"; //!< 类名
    static const int foodCost = 4;                   //!< 食物消耗
    static const g_time chewDuration = 3;            //!< 咀嚼持续时间
    g_time chewCountDown = 0;                        //!< 咀嚼倒计时

public:
    explicit HungryAnt(int health = 1);

    void action(GameState &gamestate) override;
};

#endif // HUNGRYANT_H
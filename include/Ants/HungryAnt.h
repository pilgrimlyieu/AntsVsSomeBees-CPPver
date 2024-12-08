#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.h"

class HungryAnt final : public Ant {
private:
    const g_time chewDuration; //!< 咀嚼持续时间
    g_time chewCountDown;      //!< 咀嚼倒计时

public:
    explicit HungryAnt(double health = 1.0);

    void action(GameState &gamestate) override final;
};

#endif // HUNGRYANT_H
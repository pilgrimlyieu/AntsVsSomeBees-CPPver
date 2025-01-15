#ifndef HUNGRYANT_H
#define HUNGRYANT_H

#include "Ant.hpp"

class HungryAnt final : public Ant {
private:
    const g_time chewDuration; //!< 咀嚼持续时间
    g_time chewCountDown;      //!< 咀嚼倒计时

public:
    explicit HungryAnt(double health);

    explicit HungryAnt() : HungryAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // HUNGRYANT_H
#ifndef HUNGRYANT_HPP
#define HUNGRYANT_HPP

#include "Ant.hpp"

class HungryAnt final : public Ant {
private:
    string getName() const final {
        return "HungryAnt";
    }
    int getFoodCost() const final {
        return 4;
    }

    const g_time chewDuration; //!< 咀嚼持续时间
    g_time chewCountDown;      //!< 咀嚼倒计时

public:
    explicit HungryAnt(double health) : Ant(health), chewDuration(3), chewCountDown(0) {}
    explicit HungryAnt() : HungryAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // HUNGRYANT_HPP
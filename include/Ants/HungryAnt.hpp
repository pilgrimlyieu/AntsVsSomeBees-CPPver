#ifndef HUNGRYANT_HPP
#define HUNGRYANT_HPP

#include "Ant.hpp"

class HungryAnt final : public Ant {
protected:
    string getName() const final {
        return "HungryAnt";
    }
    int getFoodCost() const final {
        return 4;
    }

    friend Ant *Ant::deserialize(const json &data);

    const g_time chewDuration; //!< 咀嚼持续时间
    g_time chewCountDown;      //!< 咀嚼倒计时

public:
    explicit HungryAnt(double health) : Ant(health), chewDuration(3), chewCountDown(0) {}
    explicit HungryAnt() : HungryAnt(1.0) {}

    void action(GameState &gamestate) final;

    json serialize() const final;
};

#endif // HUNGRYANT_HPP
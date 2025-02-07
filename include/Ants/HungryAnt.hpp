#ifndef HUNGRYANT_HPP
#define HUNGRYANT_HPP

#include "Ant.hpp"

class HungryAnt final : public Ant {
protected:
    [[nodiscard]]
    string getName() const final {
        return "HungryAnt";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 4;
    }

    friend Ant *Ant::deserialize(const json &data);

    const g_time chewDuration = 3; //!< 咀嚼持续时间
    g_time chewCountDown = 0;      //!< 咀嚼倒计时

public:
    explicit HungryAnt(double health) : Ant(health) {}
    explicit HungryAnt() : HungryAnt(1.0) {}

    void action(GameState &gamestate) final;

    [[nodiscard]]
    json serialize() const final;
};

#endif // HUNGRYANT_HPP
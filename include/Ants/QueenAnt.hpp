#ifndef QUEENANT_HPP
#define QUEENANT_HPP

#include "ScubaThrower.hpp"

class QueenAnt final : public ScubaThrower {
protected:
    [[nodiscard]]
    string getName() const final {
        return "QueenAnt";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 7;
    }

public:
    explicit QueenAnt(double health) : ScubaThrower(health) {}
    explicit QueenAnt() : QueenAnt(1.0) {}

    void action(GameState &gamestate) final;

    void reduceHealth(double amount) final;
};

#endif // QUEENANT_HPP
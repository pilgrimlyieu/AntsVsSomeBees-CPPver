#ifndef QUEENANT_HPP
#define QUEENANT_HPP

#include "ScubaThrower.hpp"

class QueenAnt final : public ScubaThrower {
public:
    explicit QueenAnt(double health);

    explicit QueenAnt() : QueenAnt(1.0) {}

    void action(GameState &gamestate) final;

    void reduceHealth(double amount) final;

    void removeFrom(Place *place) final;
};

#endif // QUEENANT_HPP
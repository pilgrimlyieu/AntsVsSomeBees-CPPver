#ifndef QUEENANT_H
#define QUEENANT_H

#include "ScubaThrower.h"

class QueenAnt final : public ScubaThrower {
public:
    explicit QueenAnt(double health);

    explicit QueenAnt() : QueenAnt(1.0) {}

    QueenAnt *construct(GameState &gamestate) override final;

    void action(GameState &gamestate) override final;

    void reduceHealth(double amount) override final;

    void removeFrom(Place *place) override final;
};

#endif // QUEENANT_H
#ifndef QUEENANT_H
#define QUEENANT_H

#include "ScubaThrower.h"

class QueenAnt final : public ScubaThrower {
private:
    inline static const std::string name = "Queen"; //!< 类名
    static const int foodCost = 7;                  //!< 食物消耗

public:
    QueenAnt *construct(GameState &gamestate) override final;

    void action(GameState &gamestate) override final;

    void reduceHealth(int amount) override final;

    void removeFrom(Place *place) override final;
};

#endif // QUEENANT_H
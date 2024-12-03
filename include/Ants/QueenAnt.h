#ifndef QUEENANT_H
#define QUEENANT_H

#include "ScubaThrower.h"

class QueenAnt : public ScubaThrower {
public:
    inline static const string name = "Queen"; //!< 类名
    static const int foodCost = 7;             //!< 食物消耗

    static QueenAnt *construct(GameState &gamestate);

    void action(GameState &gamestate) override;

    void reduceHealth(int amount);

    void removeFrom(Place *place);
};

#endif // QUEENANT_H
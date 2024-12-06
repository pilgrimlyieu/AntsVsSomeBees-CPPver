#ifndef QUEENANT_H
#define QUEENANT_H

#include "ScubaThrower.h"

class QueenAnt final : public ScubaThrower {
private:
    inline static const std::string name = "Queen"; //!< 类名
    static const int foodCost = 7;                  //!< 食物消耗

public:
    static QueenAnt *construct(GameState &gamestate);

    void action(GameState &gamestate) override;

    void reduceHealth(int amount);

    void removeFrom(Place *place) override;
};

#endif // QUEENANT_H
#ifndef QUEENANT_H
#define QUEENANT_H

#include "ScubaThrower.h"

class QueenAnt : public ScubaThrower {
public:
    string name = "Queen";         // the name of the Ant
    static const int foodCost = 7; // the food cost of the Ant

    static QueenAnt *construct(GameState &gamestate);

    void action(GameState &gamestate) override;

    void reduceHealth(int amount);

    void removeFrom(Place *place);
};

#endif // QUEENANT_H
#ifndef HIVE_H
#define HIVE_H

#include "AssaultPlan.h"
#include "Place.h"

class Hive final : public Place {
public:
    AssaultPlan *assaultPlan; // TODO initialize
    bees_list bees;

    explicit Hive(AssaultPlan *assaultPlan);

    void strategy(GameState &gameState);
};

#endif // HIVE_H
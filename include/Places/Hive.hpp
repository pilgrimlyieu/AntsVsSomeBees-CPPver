#ifndef HIVE_H
#define HIVE_H

#include "AssaultPlan.hpp"
#include "Place.hpp"

class Hive final : public Place {
public:
    AssaultPlan *assaultPlan;
    bees_list bees;

    explicit Hive(AssaultPlan *assaultPlan);

    void strategy(GameState &gameState);
};

#endif // HIVE_H
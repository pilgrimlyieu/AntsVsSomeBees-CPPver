#ifndef HIVE_HPP
#define HIVE_HPP

#include "AssaultPlan.hpp"
#include "Place.hpp"

class Hive final : public Place {
private:
    bool getIsHive() const final {
        return true;
    }

public:
    AssaultPlan assaultPlan;
    bees_list bees;

    explicit Hive(AssaultPlan assaultPlan);

    void strategy(GameState &gameState);
};

#endif // HIVE_HPP
#ifndef HIVE_HPP
#define HIVE_HPP

#include "AssaultPlan.hpp"
#include "Place.hpp"

class Hive final : public Place {
public:
    AssaultPlan assaultPlan;
    bees_list bees;

    explicit Hive(AssaultPlan aP);

    [[nodiscard]]
    bool getIsHive() const final {
        return true;
    }

    void strategy(GameState &gameState);

    [[nodiscard]]
    json serialize() const final;
};

#endif // HIVE_HPP
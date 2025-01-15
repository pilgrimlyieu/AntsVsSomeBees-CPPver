#ifndef BOSS_HPP
#define BOSS_HPP

#include "Hornet.hpp"
#include "Wasp.hpp"

class Boss final : public Wasp, public Hornet {
private:
    const double damageCap; //!< 受伤害上限

    double damageModifier(double amount);

public:
    explicit Boss(double health, Place *place);

    explicit Boss(double health) : Boss(health, nullptr) {}

    using Wasp::action;

    void reduceHealth(double amount) final;
};

#endif // BOSS_HPP
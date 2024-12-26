#ifndef BOSS_H
#define BOSS_H

#include "Hornet.h"
#include "Wasp.h"

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

#endif // BOSS_H
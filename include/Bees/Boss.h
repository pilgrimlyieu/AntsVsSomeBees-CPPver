#ifndef BOSS_H
#define BOSS_H

#include "Hornet.h"
#include "Wasp.h"

class Boss final : public Wasp, public Hornet {
private:
    const double damageCap; //!< 受伤害上限

    double damageModifier(double amount);

public:
    explicit Boss(double health = 10.0, Place *place = nullptr);

    using Wasp::action;

    void reduceHealth(double amount) override final;
};

#endif // BOSS_H
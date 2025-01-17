#ifndef BOSS_HPP
#define BOSS_HPP

#include "Wasp.hpp"

class Boss final : public Wasp {
protected:
    string getName() const override {
        return "Boss";
    }

    double damageModifier(double amount);

    const double damageCap = 8.0; //!< 受伤害上限

public:
    explicit Boss(double health, Place *place) : Wasp(health, place) {}
    explicit Boss(double health) : Boss(health, nullptr) {}

    void reduceHealth(double amount) final;
};

#endif // BOSS_HPP
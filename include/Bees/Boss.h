#ifndef BOSS_H
#define BOSS_H

#include "Hornet.h"
#include "Wasp.h"

class Boss final : public Wasp, public Hornet {
private:
    inline static const std::string name = "Boss"; //!< 类名
    constexpr static const double damageCap = 8.0; //!< 受伤害上限

    double damageModifier(int amount);

public:
    using Wasp::action;

    void reduceHealth(int amount) override final;
};

#endif // BOSS_H
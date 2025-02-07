#ifndef SHORTTHROWER_HPP
#define SHORTTHROWER_HPP

#include "ThrowerAnt.hpp"

class ShortThrower final : public ThrowerAnt {
protected:
    [[nodiscard]]
    string getName() const final {
        return "ShortThrower";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 2;
    }
    [[nodiscard]]
    int getMaxRange() const final {
        return 3;
    }

public:
    explicit ShortThrower(double health) : ThrowerAnt(health) {}

    explicit ShortThrower() : ShortThrower(1.0) {}
};

#endif // SHORTTHROWER_HPP
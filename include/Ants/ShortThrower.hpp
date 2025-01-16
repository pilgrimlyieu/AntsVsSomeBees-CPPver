#ifndef SHORTTHROWER_HPP
#define SHORTTHROWER_HPP

#include "ThrowerAnt.hpp"

class ShortThrower final : public ThrowerAnt {
private:
    string getName() const final {
        return "ShortThrower";
    }
    int getFoodCost() const final {
        return 2;
    }
    int getMaxRange() const final {
        return 3;
    }

public:
    explicit ShortThrower(double health) : ThrowerAnt(health) {}

    explicit ShortThrower() : ShortThrower(1.0) {}
};

#endif // SHORTTHROWER_HPP
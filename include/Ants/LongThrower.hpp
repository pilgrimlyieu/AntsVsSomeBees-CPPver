#ifndef LONGTHROWER_HPP
#define LONGTHROWER_HPP

#include "ThrowerAnt.hpp"

class LongThrower final : public ThrowerAnt {
protected:
    [[nodiscard]]
    string getName() const final {
        return "LongThrower";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 2;
    }
    [[nodiscard]]
    int getMinRange() const final {
        return 5;
    }

public:
    explicit LongThrower(double health) : ThrowerAnt(health) {}
    explicit LongThrower() : LongThrower(1.0) {}
};

#endif // LONGTHROWER_HPP
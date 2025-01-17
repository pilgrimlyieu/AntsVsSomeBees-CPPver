#ifndef LONGTHROWER_HPP
#define LONGTHROWER_HPP

#include "ThrowerAnt.hpp"

class LongThrower final : public ThrowerAnt {
protected:
    string getName() const final {
        return "LongThrower";
    }
    int getFoodCost() const final {
        return 2;
    }
    int getMinRange() const final {
        return 5;
    }

public:
    explicit LongThrower(double health) : ThrowerAnt(health) {}
    explicit LongThrower() : LongThrower(1.0) {}
};

#endif // LONGTHROWER_HPP
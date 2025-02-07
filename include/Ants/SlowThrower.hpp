#ifndef SLOWTHROWER_HPP
#define SLOWTHROWER_HPP

#include "ThrowerAnt.hpp"

class SlowThrower final : public ThrowerAnt {
protected:
    [[nodiscard]]
    string getName() const final {
        return "SlowThrower";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 4;
    }

    void throwAt(Bee *target) final;

public:
    explicit SlowThrower(double health) : ThrowerAnt(health) {}
    explicit SlowThrower() : SlowThrower(1.0) {};
};

#endif // SLOWTHROWER_HPP
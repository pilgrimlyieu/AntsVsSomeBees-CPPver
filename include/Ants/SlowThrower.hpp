#ifndef SLOWTHROWER_HPP
#define SLOWTHROWER_HPP

#include "ThrowerAnt.hpp"

class SlowThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) final;

public:
    explicit SlowThrower(double health);

    explicit SlowThrower() : SlowThrower(1.0) {};
};

#endif // SLOWTHROWER_HPP
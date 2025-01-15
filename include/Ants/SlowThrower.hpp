#ifndef SLOWTHROWER_H
#define SLOWTHROWER_H

#include "ThrowerAnt.hpp"

class SlowThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) final;

public:
    explicit SlowThrower(double health);

    explicit SlowThrower() : SlowThrower(1.0) {};
};

#endif // SLOWTHROWER_H
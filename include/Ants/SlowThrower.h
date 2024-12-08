#ifndef SLOWTHROWER_H
#define SLOWTHROWER_H

#include "ThrowerAnt.h"

class SlowThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) override final;

public:
    explicit SlowThrower(double health = 1.0);
};

#endif // SLOWTHROWER_H
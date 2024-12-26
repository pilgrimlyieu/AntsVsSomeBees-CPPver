#ifndef SCARYTHROWER_H
#define SCARYTHROWER_H

#include "ThrowerAnt.h"

class ScaryThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) final;

public:
    explicit ScaryThrower(double health);

    explicit ScaryThrower() : ScaryThrower(1.0) {}
};

#endif // SCARYTHROWER_H
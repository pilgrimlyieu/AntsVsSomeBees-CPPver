#ifndef SCARYTHROWER_H
#define SCARYTHROWER_H

#include "ThrowerAnt.h"

class ScaryThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) override final;

public:
    explicit ScaryThrower(double health = 1.0);
};

#endif // SCARYTHROWER_H
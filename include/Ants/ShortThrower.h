#ifndef SHORTTHROWER_H
#define SHORTTHROWER_H

#include "ThrowerAnt.h"

class ShortThrower final : public ThrowerAnt {
public:
    explicit ShortThrower(double health = 1.0);
};

#endif // SHORTTHROWER_H
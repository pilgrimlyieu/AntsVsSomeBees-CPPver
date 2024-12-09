#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include "ThrowerAnt.h"

class LongThrower final : public ThrowerAnt {
public:
    explicit LongThrower(double health);

    explicit LongThrower() : LongThrower(1.0) {}
};

#endif // LONGTHROWER_H
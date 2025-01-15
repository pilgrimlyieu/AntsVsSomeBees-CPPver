#ifndef LONGTHROWER_HPP
#define LONGTHROWER_HPP

#include "ThrowerAnt.hpp"

class LongThrower final : public ThrowerAnt {
public:
    explicit LongThrower(double health);

    explicit LongThrower() : LongThrower(1.0) {}
};

#endif // LONGTHROWER_HPP
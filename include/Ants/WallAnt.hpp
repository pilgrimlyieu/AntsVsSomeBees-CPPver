#ifndef WALLANT_HPP
#define WALLANT_HPP

#include "Ant.hpp"

class WallAnt final : public Ant {
public:
    explicit WallAnt(double health);

    explicit WallAnt() : WallAnt(4.0) {}
};

#endif // WALLANT_HPP
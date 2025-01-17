#ifndef WALLANT_HPP
#define WALLANT_HPP

#include "Ant.hpp"

class WallAnt final : public Ant {
protected:
    string getName() const final {
        return "WallAnt";
    }
    int getFoodCost() const final {
        return 4;
    }

public:
    explicit WallAnt(double health) : Ant(health) {}
    explicit WallAnt() : WallAnt(4.0) {}
};

#endif // WALLANT_HPP
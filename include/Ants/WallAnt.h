#ifndef WALLANT_H
#define WALLANT_H

#include "Ant.h"

class WallAnt final : public Ant {
public:
    explicit WallAnt(double health = 4.0);
};

#endif // WALLANT_H
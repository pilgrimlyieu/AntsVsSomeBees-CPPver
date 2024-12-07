#ifndef WALLANT_H
#define WALLANT_H

#include "Ant.h"

class WallAnt final : public Ant {
private:
    inline static const std::string name = "Wall"; //!< 类名
    static const int foodCost = 4;                 //!< 食物消耗

public:
    explicit WallAnt(double health = 4.0);
};

#endif // WALLANT_H
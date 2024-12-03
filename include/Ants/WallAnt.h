#ifndef WALLANT_H
#define WALLANT_H

#include "Ant.h"

class WallAnt : public Ant {
public:
    inline static const string name = "Wall"; //!< 类名
    static const int foodCost = 4;            //!< 食物消耗

    WallAnt(int health = 4);
};

#endif // WALLANT_H
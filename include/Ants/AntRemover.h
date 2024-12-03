#ifndef ANTREMOVER_H
#define ANTREMOVER_H

#include "Ant.h"

class AntRemover : public Ant {
public:
    inline static const string name = "Remover"; //!< 类名
    static const int foodCost = 1;               //!< 食物消耗（没错，Remover 工具也要消耗）

    AntRemover(int health = 0);
};

#endif // ANTREMOVER_H
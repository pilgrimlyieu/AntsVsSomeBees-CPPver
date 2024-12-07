#ifndef ANTREMOVER_H
#define ANTREMOVER_H

#include "Ant.h"

class AntRemover final : public Ant {
private:
    inline static const std::string name = "Remover"; //!< 类名
    static const int foodCost = 1;                    //!< 食物消耗（没错，Remover 工具也要消耗）

public:
    explicit AntRemover(double health = 0.0);
};

#endif // ANTREMOVER_H
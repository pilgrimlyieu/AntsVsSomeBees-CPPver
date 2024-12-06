#ifndef BODYGUARDANT_H
#define BODYGUARDANT_H

#include "ContainerAnt.h"

class BodyguardAnt final : public ContainerAnt {
private:
    inline static const std::string name = "Bodyguard"; //!< 类名
    static const int foodCost = 4;                      //!< 食物消耗

public:
    explicit BodyguardAnt(int health = 2);
};

#endif // BODYGUARDANT_H
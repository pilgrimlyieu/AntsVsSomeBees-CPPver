#ifndef HORNET_H
#define HORNET_H

#include "Bee.h"

class Hornet : public Bee {
private:
    inline static const std::string name = "Hornet"; //!< 类名
    constexpr static const double damage = 0.25;     //!< 伤害

public:
    void action(GameState &gamestate) override final;

    // TODO: __setattr__
};

#endif // HORNET_H
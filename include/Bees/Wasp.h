#ifndef WASP_H
#define WASP_H

#include "Bee.h"

class Wasp : public Bee {
private:
    inline static const std::string name = "Wasp"; //!< 类名
    constexpr static const double damage = 2.0;    //!< 伤害
};

#endif // WASP_H
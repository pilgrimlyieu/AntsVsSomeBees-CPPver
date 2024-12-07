#ifndef NINJABEE_H
#define NINJABEE_H

#include "Bee.h"

class NinjaBee final : public Bee {
private:
    inline static const std::string name = "Ninja"; //!< 类名

public:
    bool blocked() override final;
};

#endif // NINJABEE_H
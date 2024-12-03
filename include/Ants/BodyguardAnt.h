#ifndef BODYGUARDANT_H
#define BODYGUARDANT_H

#include "ContainerAnt.h"

class BodyguardAnt : public ContainerAnt {
public:
    inline static const string name = "Bodyguard"; //!< 类名

    BodyguardAnt(int health = 2);
};

#endif // BODYGUARDANT_H
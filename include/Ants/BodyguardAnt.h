#ifndef BODYGUARDANT_H
#define BODYGUARDANT_H

#include "ContainerAnt.h"

class BodyguardAnt final : public ContainerAnt {
public:
    explicit BodyguardAnt(double health);

    explicit BodyguardAnt() : BodyguardAnt(2.0) {}
};

#endif // BODYGUARDANT_H
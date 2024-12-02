#ifndef BODYGUARDANT_H
#define BODYGUARDANT_H

#include "ContainerAnt.h"

class BodyguardAnt : public ContainerAnt {
public:
    string name = "Bodyguard"; // the name of the Ant

    BodyguardAnt(int health = 2);
};

#endif // BODYGUARDANT_H
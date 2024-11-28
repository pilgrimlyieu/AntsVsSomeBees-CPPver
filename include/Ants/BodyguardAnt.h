#ifndef BODYGUARDANT_H
#define BODYGUARDANT_H

#include "ContainerAnt.h"

class BodyguardAnt : public ContainerAnt {
  public:
    string name = "Bodyguard";

    BodyguardAnt(int health = 2);
};

#endif // BODYGUARDANT_H
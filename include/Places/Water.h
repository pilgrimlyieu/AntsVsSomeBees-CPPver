#ifndef WATER_H
#define WATER_H

#include "Place.h"

class Water : public Place {
  public:
    void addInsect(Insect *insect);
};

#endif // WATER_H
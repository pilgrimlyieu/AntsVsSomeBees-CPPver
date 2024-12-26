#ifndef WATER_H
#define WATER_H

#include "Place.h"

class Water final : public Place {
public:
    using Place::Place;

    void addInsect(Insect *insect) final;
};

#endif // WATER_H
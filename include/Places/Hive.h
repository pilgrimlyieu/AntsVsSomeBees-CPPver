#ifndef HIVE_H
#define HIVE_H

#include "Place.h"

class Hive : public Place {
public:
    static const bool isHive = true; // whether this place is a hive
    Hive(); // TODO: Add `assaultPlan`
};

#endif // HIVE_H
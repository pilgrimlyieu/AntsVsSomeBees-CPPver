#ifndef HIVE_H
#define HIVE_H

#include "Place.h"

class Hive final : public Place {
public:
    static const bool isHive = true; //!< 是否是 Hive

    explicit Hive(); // TODO: Add `assaultPlan`
};

#endif // HIVE_H
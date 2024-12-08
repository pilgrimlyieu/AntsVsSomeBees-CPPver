#ifndef ASSAUTPLAN_H
#define ASSAUTPLAN_H

#include "Utilities.h"

class AssaultPlan final {
private:
    std::map<g_time, bee_list> waves;

public:
    AssaultPlan &addWave(bee_t beeType, double beeHealth, g_time time, int count);

    bee_list getBees() const;
};

#endif // ASSAUTPLAN_H
#ifndef ASSAUTPLAN_H
#define ASSAUTPLAN_H

#include "Utilities.h"

class AssaultPlan final {
private:
    std::map<g_time, std::vector<Bee *>> waves;

public:
    AssaultPlan &addWave(Bee_t beeType, double beeHealth, g_time time, int count);

    std::vector<Bee *> getBees() const;
};

#endif // ASSAUTPLAN_H
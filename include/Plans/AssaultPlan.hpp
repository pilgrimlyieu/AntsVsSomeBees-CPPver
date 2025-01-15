#ifndef ASSAUTPLAN_H
#define ASSAUTPLAN_H

#include "Utilities.hpp"
class AssaultPlan final {
private:
    map<g_time, bees_list> waves;

public:
    AssaultPlan &addWave(bee_type beeType, double beeHealth, g_time time, int count);

    [[nodiscard]]
    bees_list getBees() const;

    bees_list &operator[](g_time time);
};

#endif // ASSAUTPLAN_H
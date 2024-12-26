#ifndef ASSAUTPLAN_H
#define ASSAUTPLAN_H

#include "Utilities.h"
class AssaultPlan final {
private:
    map<g_time, bee_list> waves;

public:
    AssaultPlan &addWave(bee_type beeType, double beeHealth, g_time time, int count);

    [[nodiscard]]
    bee_list getBees() const;

    bee_list &operator[](g_time time);
};

#endif // ASSAUTPLAN_H
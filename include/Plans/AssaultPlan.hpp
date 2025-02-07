#ifndef ASSAUTPLAN_HPP
#define ASSAUTPLAN_HPP

#include "Serializable.hpp"
#include "Utilities.hpp"

class AssaultPlan final : public Serializable {
private:
    map<g_time, bees_list> waves;

public:
    AssaultPlan &addWave(bee_type beeType, double beeHealth, g_time time, int count);

    void timeReleased(g_time time);

    [[nodiscard]]
    bees_list getBees() const;

    [[nodiscard]]
    bees_list &operator[](g_time time);

    [[nodiscard]]
    json serialize() const final;
    [[nodiscard]]
    static AssaultPlan deserialize(const json &data);
};

#endif // ASSAUTPLAN_HPP
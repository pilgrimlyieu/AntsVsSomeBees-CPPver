#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.hpp"

class ContainerAnt : public Ant {
protected:
    struct container_ant_properties : ant_properties {
        string name = "ContainerAnt"; //!< 类名
    };

    explicit ContainerAnt(double health,
                          container_ant_properties properties); //!< 抽象类，不可实例化

    explicit ContainerAnt(double health) : ContainerAnt(health, {}) {}

    explicit ContainerAnt() : ContainerAnt(1.0) {}

public:
    Ant *antContained; //!< 容纳的 Ant

    bool canContain(Ant *other) final;

    void storeAnt(Ant *ant) final;

    void removeAnt(Ant *ant) final;

    void removeFrom(Place *place) final;

    void action(GameState &gamestate) override;
};

#endif // CONTAINERANT_H
#ifndef CONTAINERANT_HPP
#define CONTAINERANT_HPP

#include "Ant.hpp"

class ContainerAnt : public Ant {
protected:
    [[nodiscard]]
    string getName() const override {
        return "ContainerAnt";
    }

    explicit ContainerAnt(double health) : Ant(health) {}
    explicit ContainerAnt() : ContainerAnt(1.0) {}

public:
    Ant *antContained = nullptr; //!< 容纳的 Ant

    bool canContain(Ant *other) final;

    void storeAnt(Ant *ant) final;

    void removeAnt(Ant *ant) final;

    void removeFrom(Place *place) final;

    void action(GameState &gamestate) override;

    [[nodiscard]]
    json serialize() const override;
};

#endif // CONTAINERANT_HPP
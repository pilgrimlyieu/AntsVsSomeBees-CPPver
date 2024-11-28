#include "ContainerAnt.h"
#include "GameState.h"
#include "Place.h"

ContainerAnt::ContainerAnt(int health) : Ant(health), antContained(nullptr) {}

bool ContainerAnt::canContain(Ant *other) {
    return antContained == nullptr && !other->isContainer;
}

void ContainerAnt::storeAnt(Ant *ant) {
    antContained = ant;
}

void ContainerAnt::removeAnt(Ant *ant) {
    if (antContained != ant) {
        // "{this} does not contain {other}"
        throw invalid_argument(string(*this) + " does not contain " + string(*ant));
    }
    antContained = nullptr;
}

void ContainerAnt::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = ((ContainerAnt *)place->ant)->antContained;
        Insect::removeFrom(place);
    } else {
        Ant::removeFrom(place);
    }
}

void ContainerAnt::action(GameState &gamestate) {
    if (antContained != nullptr) {
        antContained->action(gamestate);
    }
}
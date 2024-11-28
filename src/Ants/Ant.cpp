#include "Ant.h"
#include "GameState.h"
#include "Place.h"

Ant::Ant(int health) : Insect(health, nullptr), buffed(false) {}

Ant *Ant::construct(GameState &gamestate) {
    if (foodCost > gamestate.food) {
        return nullptr;
    }
    return new Ant();
}

bool Ant::canContain(Ant *other) {
    return false;
}

void Ant::storeAnt(Ant *other) {}

void Ant::removeAnt(Ant *other) {}

void Ant::addTo(Place *place) {
    if (place->ant == nullptr) {
        place->ant = this;
    } else {
        if (place->ant->canContain(this)) {
            place->ant->storeAnt(this);
        } else if (canContain(place->ant)) {
            storeAnt(place->ant);
            place->ant = this;
        } else if (place->ant->place != nullptr) {
            // "Two ants in one place: {place->name}"
            throw invalid_argument("Two ants in one place: " + place->name);
        }
    }
    Insect::addTo(place);
}

void Ant::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = nullptr;
    } else if (place->ant == nullptr) {
        // "Ant is not in {place->name}"
        throw invalid_argument("Ant is not in " + place->name);
        // TODO: Add `str` method
    } else {
        removeAnt(place->ant);
    }
    Insect::removeFrom(place);
}

void Ant::buff() {
    if (!buffed) {
        damage *= 2;
        buffed = true;
    }
}
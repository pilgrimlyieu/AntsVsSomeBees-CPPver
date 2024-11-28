#include "ThrowerAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

Bee *ThrowerAnt::nearestBee() {
    Place *place = this->place;
    int distance = 0;
    while (!place->isHive) {
        if (place->bees.size() > 0 && distance >= minRange && distance <= maxRange) {
            return place->randomBee();
        }
        distance++;
        place = place->entrance;
    }
    return nullptr;
}

void ThrowerAnt::throwAt(Bee *target) {
    if (target != nullptr) {
        target->reduceHealth(damage);
    }
}

void ThrowerAnt::action(GameState &gamestate) {
    throwAt(nearestBee());
}
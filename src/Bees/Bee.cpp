#include "Bee.h"
#include "Ant.h"
#include "Place.h"

Bee::Bee(int health, Place *place) : Insect(health, place) {}

void Bee::sting(Ant *ant) {
    ant->reduceHealth(damage);
}

void Bee::moveTo(Place *place) {
    place->removeInsect(this);
    place->addInsect(this);
}

bool Bee::blocked() {
    return place->ant != nullptr && place->ant->blocksPath;
}

void Bee::addTo(Place *place) {
    place->bees.push_back(this);
    Insect::addTo(place);
}

void Bee::removeFrom(Place *place) {
    place->bees.remove(this);
    Insect::removeFrom(place);
}

void Bee::slow(g_time length) {
    slowedTime += length;
}

void Bee::scare(g_time length) {
    if (!isScared) {
        scaredTime += length;
        isScared = true;
    }
}

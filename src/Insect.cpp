#include "Insect.h"
#include "Place.h"

Insect::Insect(int health, Place *place) {
    this->health = health;
    this->place = place;
}

void Insect::reduceHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        deathCallback();
        place->removeInsect(this);
    }
}

void Insect::addTo(Place *place) {
    this->place = place;
}

void Insect::removeFrom(Place *place) {
    this->place = nullptr;
}

Insect::operator string() const {
    // "Insect({health}, {damage})"
    return "Insect(" + to_string(health) + ", " + to_string(damage) + ")";
}

void Insect::kill() {
    reduceHealth(health);
}
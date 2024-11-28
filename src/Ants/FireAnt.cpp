#include "FireAnt.h"
#include "Bee.h"
#include "Place.h"

void FireAnt::reduceHealth(int amount) {
    int totalDamage = amount + ((amount >= health) ? damage : 0);
    vector<Bee *> killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= totalDamage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(totalDamage);
    }
    Insect::reduceHealth(amount);
}
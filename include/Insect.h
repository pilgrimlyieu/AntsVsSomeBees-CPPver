#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

using namespace std;

class Insect {
  public:
    static const bool isWaterProof = false; // whether this insect is waterproof
    int damage = 0;                         // the amount of damage this insect deals
    int health;                             // the current health of this insect
    Place *place;                           // the place where this insect is located

    Insect(int health, Place *place);

    void reduceHealth(int amount);

    void action(GameState &gamestate);

    void deathCallback();

    void addTo(Place *place);

    void removeFrom(Place *place);

    operator string() const;

    void kill();
};

#endif // INSECT_H
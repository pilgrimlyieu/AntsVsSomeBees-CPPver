#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

using namespace std;

class Insect {
public:
    string name = "Insect";                 // the name of this insect
    static const bool isWaterProof = false; // the water proof ability of this insect
    int damage = 0;                         // the amount of damage this insect deals
    int health;                             // the current health of this insect
    Place *place;                           // the place where this insect is located

    Insect(int health, Place *place);

    void reduceHealth(int amount);

    virtual void action(GameState &gamestate) = 0;

    void injuryCallback();

    void deathCallback();

    void addTo(Place *place);

    void removeFrom(Place *place);

    operator string() const;

    void kill();

    virtual ~Insect() = default;
};

#endif // INSECT_H
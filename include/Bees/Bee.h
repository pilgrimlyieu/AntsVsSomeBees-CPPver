#ifndef BEE_H
#define BEE_H

#include "Insect.h"

class Bee : public Insect {
public:
    string name = "Bee";                   // the name of the Bee
    static const int damage = 1;           // the damage of the Bee
    static const bool isWaterProof = true; // the water proof ability of the Bee
    g_time slowedTime = 0;                 // the time the Bee is slowed
    g_time scaredTime = 0;                 // the time the Bee is scared
    bool isScared = false;                 // the scared status of the Bee

    Bee(int health, Place *place = nullptr);

    void sting(Ant *ant);

    void moveTo(Place *place);

    bool blocked();

    void action(GameState &gamestate) override;

    void injuryCallback();

    void deathCallback();

    void addTo(Place *place);

    void removeFrom(Place *place);

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H
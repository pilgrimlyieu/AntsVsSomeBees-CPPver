#include "HungryAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

HungryAnt::HungryAnt(int health) : Ant(health), chewCountDown(0) {}

void HungryAnt::action(GameState &gamestate) {
    if (chewCountDown == 0) {
        Bee *bee = place->randomBee();
        if (bee != nullptr) {
            chewCountDown = chewDuration;
            bee->kill();
        }
    } else {
        chewCountDown--;
    }
}
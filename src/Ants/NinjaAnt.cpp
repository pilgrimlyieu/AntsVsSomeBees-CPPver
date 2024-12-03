#include "NinjaAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 执行 NinjaAnt 的动作
 *
 * NinjaAnt 的动作是对当前位置的所有 Bee 造成伤害。
 */
void NinjaAnt::action(GameState &gamestate) {
    vector<Bee *> killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= damage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(damage);
    }
}
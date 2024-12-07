#include "HungryAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 HungryAnt
 *
 * @param health HungryAnt 的初始生命值，默认为 1
 */
HungryAnt::HungryAnt(double health) : Ant(health) {}

/**
 * @brief 执行 HungryAnt 的动作
 *
 * HungryAnt 的动作是吃掉当前 Place 随机的一个 Bee 。
 *
 * 每次 HungryAnt 吃掉一个 Bee 后，需要等待 chewDuration 回合后才能再次吃掉 Bee 。
 *
 * @param gamestate 当前的游戏状态。
 */
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
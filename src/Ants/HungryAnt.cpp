#include "HungryAnt.hpp"
#include "Bee.hpp"
#include "GameState.hpp"
#include "Place.hpp"

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
            log(LOGINFO, format("{} eats {}", *this, *bee));
            chewCountDown = chewDuration;
            bee->kill();
        }
    } else {
        log(LOGTEST, format("{} is chewing, {} rounds left", *this, chewCountDown));
        chewCountDown--;
    }
}
#include "Hornet.h"
#include "GameState.h"

/**
 * @brief 构造一个新的 Hornet
 *
 * 默认 Hornet 的属性：
 *
 * - 类名 name 为 "Hornet"
 *
 * - 伤害 damage 为 0.25
 *
 * @param health Hornet 的初始生命值，默认为 1.0
 * @param place 指向 Hornet 所在的 Place 的指针，默认为 `nullptr`
 */
Hornet::Hornet(double health, Place *place)
    : Bee(health, place,
          {
              .name = "Hornet",
              .damage = 0.25,
          }) {}

/**
 * @brief 执行 Hornet 的动作
 *
 * Hornet 每轮能执行两次动作。
 */
void Hornet::action(GameState &gamestate) {
    const int repeat = 2;
    for (int i = 0; i < repeat; i++) {
        if (health > 0.0) {
            Bee::action(gamestate);
        }
    }
}
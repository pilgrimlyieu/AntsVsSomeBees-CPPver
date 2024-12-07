#include "Hornet.h"
#include "GameState.h"

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
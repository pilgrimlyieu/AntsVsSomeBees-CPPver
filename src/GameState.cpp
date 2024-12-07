#include "GameState.h"
#include "AntsLoseException.h"
#include "AntsWinException.h"

/**
 * @brief 使蚂蚁获胜
 *
 * 使蚂蚁获胜，抛出 AntsWinException 。
 *
 * @throw AntsWinException
 */
void antsWin() {
    throw AntsWinException();
}

/**
 * @brief 使蚂蚁失败
 *
 * 使蚂蚁失败，抛出 AntsLoseException 。
 *
 * @throw AntsLoseException
 */
void antsLose() {
    throw AntsLoseException();
}
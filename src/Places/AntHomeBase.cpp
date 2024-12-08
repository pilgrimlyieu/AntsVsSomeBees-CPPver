#include "AntHomeBase.h"
#include "Bee.h"
#include "GameState.h"

/**
 * @brief 构造一个新的 AntHomeBase
 *
 * 默认 AntHomeBase 的属性：
 *
 * - 类名 name 为 "AntHomeBase"
 *
 * @param name AntHomeBase 的名称
 * @param exit AntHomeBase 的出口
 */
AntHomeBase::AntHomeBase(std::string name, Place *exit) : Place(name, exit) {}

/**
 * @brief 将一个 Insect 添加到当前 AntHomeBase
 *
 * 若添加的 Insect 是 Bee ，则使蚂蚁失败。
 *
 * 不可在 AntHomeBase 中添加 Ant 。
 *
 * @param insect 指向要添加的 Insect 的指针
 */
void AntHomeBase::addInsect(Insect *insect) {
    if (dynamic_cast<Bee *>(insect) != nullptr) {
        antsLose();
    }
}
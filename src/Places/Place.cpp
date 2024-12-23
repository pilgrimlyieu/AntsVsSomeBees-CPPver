#include "Place.h"
#include "Insect.h"

/**
 * @brief 从当前 Place 随机选择一个 Bee
 *
 * 若当前 Place 中没有 Bee ，则返回 `nullptr`。
 *
 * @return 指向随机选择的 Bee 的指针，若没有 Bee 则返回 `nullptr`。
 */
Bee *Place::randomBee() {
    return randomElement(bees);
}

/**
 * @brief Place 类的构造函数，初始化一个 Place
 *
 * 默认 Place 的属性：
 *
 * - 是否是 Hive isHive 为 false
 *
 * @param name Place 的名称
 * @param exit Place 的出口
 */
Place::Place(string name, Place *exit, place_properties properties)
    : name(name), isHive(properties.isHive), exit(exit) {
    if (this->exit != nullptr) {
        this->exit->entrance = this;
    }
}

/**
 * @brief 将一个 Insect 添加到当前 Place
 *
 * @param insect 指向要添加的 Insect 的指针
 */
void Place::addInsect(Insect *insect) {
    insect->addTo(this);
}

/**
 * @brief 从当前 Place 中移除一个 Insect
 *
 * @param insect 指向要移除的 Insect 的指针
 */
void Place::removeInsect(Insect *insect) {
    insect->removeFrom(this);
}

/**
 * @brief 重载 string 类型转换运算符，将 Place 转换为 string
 *
 * @return string Place 的名称
 */
Place::operator string() const {
    return name;
}

/**
 * @brief Place 类的析构函数
 */
Place::~Place() {}
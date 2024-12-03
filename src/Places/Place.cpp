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
    if (bees.size() == 0) {
        return nullptr;
    }
    return get(bees, rand() % bees.size());
}

/**
 * @brief Place 类的构造函数，初始化一个 Place
 *
 * @param name Place 的名称
 * @param exit Place 的出口
 */
Place::Place(string name, Place *exit) {
    this->name = name;
    this->exit = exit;
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
 * @brief 重载 << 运算符，将一个 Insect 添加到当前 Place
 *
 * @param insect 指向要添加的 Insect 的指针
 * @return 指向当前 Place 的引用
 *
 * @example
 * @code
 * Place place;
 * Insect* insect = new Insect();
 * place << insect; // 将 Insect 添加到 Place 中
 * @endcode
 */
Place &Place::operator<<(Insect *insect) {
    addInsect(insect);
    return *this;
}

/**
 * @brief 重载 >> 运算符，将一个 Insect 从当前 Place 中移除
 *
 * @param insect 指向要移除的 Insect 的指针
 * @return 指向当前 Place 的引用
 *
 * @example
 * @code
 * Place place;
 * Insect* insect = new Insect();
 * place << insect; // 将 Insect 添加到 Place 中
 * place >> insect; // 将 Insect 从 Place 中移除
 * @endcode
 */
Place &Place::operator>>(Insect *insect) {
    removeInsect(insect);
    return *this;
}

/**
 * @brief 重载 string 类型转换运算符，将 Place 转换为 string
 *
 * @return Place 的名称
 */
Place::operator string() const {
    return name;
}

/**
 * @brief Place 类的析构函数
 */
Place::~Place() {}
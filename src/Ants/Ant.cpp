#include "Ant.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Ant 类的构造函数，初始化一个 Ant
 *
 * 默认 Ant 的属性：
 *
 * - 类名 name 为 "Ant"
 *
 * - 食物消耗 foodCost 为 0
 *
 * - 是否被加成 buffed 为 false
 *
 * - 是否可以容纳其他 Ant isContainer 为 false
 *
 * - 是否阻挡路径 blocksPath 为 true
 *
 * @param health Ant 的初始生命值，默认为 1.0
 * @param properties Ant 的属性
 */
Ant::Ant(double health, ant_properties properties)
    : Insect(health, nullptr, properties), foodCost(properties.foodCost), buffed(properties.buffed),
      isContainer(properties.isContainer), blocksPath(properties.blocksPath) {}

/**
 * @brief 构造一个新的 Ant
 *
 * 在食物充足的情况下，构造一个新的 Ant 。
 *
 * @param gamestate 当前游戏状态的引用
 * @return 若食物成本大于游戏状态中的食物数量，返回 `nullptr`；否则返回一个新的 Ant
 */
Ant *Ant::construct(GameState &gamestate) {
    if (foodCost > gamestate.food) {
        return nullptr;
    }
    return new Ant();
}

/**
 * @brief 执行 Ant 的动作
 *
 * 这个函数定义了 Ant 在给定 GameState 下的具体行为。
 *
 * @param gamestate 当前的游戏状态。
 */
void Ant::action(GameState &gamestate) {
    // TODO
}

/**
 * @brief 受伤回调函数
 *
 * 当 Ant 受伤时调用此函数。
 */
void Ant::injuryCallback() {
    // TODO
}

/**
 * @brief 死亡回调函数
 *
 * 当 Ant 死亡时调用此函数。
 */
void Ant::deathCallback() {
    // TODO
}

/**
 * @brief 判断当前 Ant 是否可以容纳另一个 Ant
 *
 * 默认 Ant 始终不能容纳其他 Ant 。
 *
 * @param other 指向另一个 Ant 的指针。
 * @return 若当前 Ant 可以容纳 other，则返回 true；否则返回 false。
 */
bool Ant::canContain(Ant *other) {
    return false;
}

/**
 * @brief 容纳另一个 Ant
 *
 * 默认 Ant 不能容纳其他 Ant ，因此调用此函数会抛出异常。
 *
 * @param other 指向要容纳的另一只 Ant 的指针。
 * @throws std::invalid_argument 当不能容纳另一只 Ant 时抛出异常。
 */
void Ant::storeAnt(Ant *other) {
    THROW_EXCEPTION(std::invalid_argument,
                    std::format("{} cannot contain {}", (std::string) * this, (std::string)*other));
}

/**
 * @brief 从当前 Ant 中移除另一个 Ant
 *
 * 默认 Ant 不能容纳其他 Ant ，因此调用此函数会抛出异常。
 *
 * @param other 指向要移除的 Ant 的指针。
 * @throws std::invalid_argument 当不能容纳另一只 Ant 时抛出异常。
 */
void Ant::removeAnt(Ant *other) {
    THROW_EXCEPTION(std::invalid_argument,
                    std::format("{} cannot contain {}", (std::string) * this, (std::string)*other));
}

/**
 * @brief 将当前 Ant 添加到指定的 Place 中
 *
 * 若 Place 中没有 Ant ，则将当前 Ant 添加到 Place 中。
 *
 * 若 Place 中已经有 Ant ，则按照以下顺序处理：
 *
 * 1. 若 Place 中的 Ant 可以容纳当前 Ant ，则当前 Ant 由其容纳；
 *
 * 2. 若当前 Ant 可以容纳 Place 中的 Ant ，则 Place 中的 Ant 由当前 Ant 容纳；
 *
 * 3. 否则，抛出异常。
 *
 * @param place 指向要添加到的 Place 的指针。
 * @throws std::invalid_argument 若当前 Ant 不能容纳 Place 中的 Ant 。
 */
void Ant::addTo(Place *place) {
    if (place->ant == nullptr) {
        place->ant = this;
    } else {
        if (place->ant->canContain(this)) {
            place->ant->storeAnt(this);
        } else if (canContain(place->ant)) {
            storeAnt(place->ant);
            place->ant = this;
        } else {
            THROW_EXCEPTION(std::invalid_argument,
                            std::format("Two ants in {}", (std::string)*place));
        }
    }
    Insect::addTo(place);
}

/**
 * @brief 从指定的 Place 中移除当前 Ant
 *
 * 若当前 Ant 在 Place 中，则将其从 Place 中移除。
 *
 * 若当前 Ant 不在 Place 中，则抛出异常。
 *
 * @param place 指向要移除的 Place 的指针。
 * @throws std::invalid_argument 若当前 Ant 不在 Place 中。
 */
void Ant::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = nullptr;
    } else if (place->ant == nullptr) {
        THROW_EXCEPTION(std::invalid_argument,
                        std::format("{} is not in {}", (std::string) * this, (std::string)*place));
    } else {
        removeAnt(place->ant);
    }
    Insect::removeFrom(place);
}

/**
 * @brief 重载 << 运算符，将另一个 Ant 容纳到当前 Ant 中
 *
 * @param other 指向要添加的 Ant 的指针。
 * @return 返回当前 Ant 的指针。
 *
 * @example
 * @code
 * Ant *ant1 = new ContainerAnt();
 * Ant *ant2 = new Ant();
 * *ant1 << ant2; // ant1 容纳了 ant2
 * @endcode
 */
Ant &Ant::operator<<(Ant *other) {
    storeAnt(other);
    return *this;
}

/**
 * @brief 重载 >> 运算符，将当前 Ant 从另一个 Ant 中移除
 *
 * @param other 指向要移除的 Ant 的指针。
 * @return 返回当前 Ant 的指针。
 *
 * @example
 * @code
 * Ant *ant1 = new ContainerAnt();
 * Ant *ant2 = new Ant();
 * *ant1 << ant2; // ant1 容纳了 ant2
 * *ant1 >> ant2; // ant1 移除了 ant2
 * @endcode
 */
Ant &Ant::operator>>(Ant *other) {
    removeAnt(other);
    return *this;
}

/**
 * @brief 为当前 Ant 加成
 *
 * 若当前 Ant 尚未被加成，则将其攻击力翻倍。
 */
void Ant::buff() {
    if (!buffed) {
        damage *= 2;
        buffed = true;
    }
}
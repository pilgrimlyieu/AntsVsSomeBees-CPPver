#include "Place.hpp"
#include "Ant.hpp"
#include "AntHomeBase.hpp"
#include "Bee.hpp"
#include "ContainerAnt.hpp"
#include "Hive.hpp"
#include "Insect.hpp"
#include "Water.hpp"

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
Place::Place(string name, Place *exit) : name(name), exit(exit) {
    if (this->exit != nullptr) {
        this->exit->entrance = this;
    }
}

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
    return format("{1}{2}{0}", ANSI_RESET, ANSI_CYAN, name);
}

/**
 * @brief 序列化当前 Place
 *
 * @return Place 的序列化 JSON 对象
 */
json Place::serialize() const {
    json j;
    j["type"] = "Place";
    j["name"] = name;
    j["exit_name"] = exit ? exit->name : "";
    j["entrance_name"] = entrance ? entrance->name : "";
    if (ant != nullptr) {
        j["ant"] = ant->serialize();
    }
    j["bees"] = json::array();
    for (const auto &bee : bees) {
        j["bees"].push_back(bee->serialize());
    }
    return j;
}

/**
 * @brief 从 JSON 对象反序列化得到 Place
 *
 * @param data Place 的 JSON 对象
 * @return 反序列化得到的 Place 指针
 */
Place *Place::deserialize(const json &data) {
    Place *place = nullptr;
    string type = data["type"];
    if (type == "Place") {
        place = new Place(data["name"]);
    } else if (type == "AntHomeBase") {
        place = new AntHomeBase(data["name"]);
    } else if (type == "Hive") {
        place = new Hive(AssaultPlan::deserialize(data["assaultPlan"]));
    } else if (type == "Water") {
        place = new Water(data["name"]);
    }
    if (place) {
        if (data.contains("ant")) {
            auto ant = Ant::deserialize(data["ant"]);
            place->addInsect(ant);
            auto containerAnt = dynamic_cast<ContainerAnt *>(ant);
            if (containerAnt) {
                containerAnt->antContained->setPlace(place);
            }
        }
        if (type != "Hive") {
            for (const auto &beeData : data["bees"]) {
                place->addInsect(Bee::deserialize(beeData));
            }
        }
    }
    return place;
}
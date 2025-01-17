#include "Water.hpp"
#include "Insect.hpp"

/**
 * @brief 将一个 Insect 添加到当前 Water
 *
 * 若 Insect 不抗水，则立即杀死。
 *
 * @param insect 指向要添加的 Insect 的指针
 */
void Water::addInsect(Insect *insect) {
    Place::addInsect(insect);
    if (!insect->getIsWaterProof()) {
        insect->kill();
    }
}

/**
 * @brief 序列化当前 Water
 *
 * @return 当前 Water 的序列化 JSON 对象。
 */
json Water::serialize() const {
    json j = Place::serialize();
    j["type"] = "Water";
    return j;
}
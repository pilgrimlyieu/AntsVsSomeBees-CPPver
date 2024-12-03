#include "Water.h"
#include "Insect.h"

/**
 * @brief 将一个 Insect 添加到当前 Water
 *
 * 若 Insect 不抗水，则立即杀死。
 *
 * @param insect 指向要添加的 Insect 的指针
 */
void Water::addInsect(Insect *insect) {
    Place::addInsect(insect);
    if (!insect->isWaterProof) {
        insect->kill();
    }
}
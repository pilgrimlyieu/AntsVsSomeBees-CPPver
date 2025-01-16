#include "AntFactory.hpp"
#include "AntRemover.hpp"
#include "BodyguardAnt.hpp"
#include "FireAnt.hpp"
#include "GameState.hpp"
#include "HarvestAnt.hpp"
#include "HungryAnt.hpp"
#include "LaserAnt.hpp"
#include "LongThrower.hpp"
#include "NinjaAnt.hpp"
#include "QueenAnt.hpp"
#include "ScaryThrower.hpp"
#include "ScubaThrower.hpp"
#include "ShortThrower.hpp"
#include "SlowThrower.hpp"
#include "TankAnt.hpp"
#include "ThrowerAnt.hpp"
#include "WallAnt.hpp"

QueenAnt *AntFactory::queenAnt = nullptr;

/**
 * @brief 获取 AntFactory 的单例
 *
 * @return AntFactory 的单例
 */
AntFactory &AntFactory::getInstance() {
    static AntFactory instance;
    return instance;
}

/**
 * @brief 重置 QueenAnt
 */
void AntFactory::resetQueenAnt() {
    if (queenAnt != nullptr) {
        delete queenAnt;
        queenAnt = nullptr;
    }
}

/**
 * @brief 注册一个 Ant 类
 *
 * @param name Ant 的名称
 * @param constructor 一个函数，返回一个新的 Ant
 */
void AntFactory::registerAnt(const string &name, ant_constructor constructor, int foodCost) {
    antConstructors[name] = constructor;
    antCosts[name] = foodCost;
    log(LOGTEST, format("Registered Ant: {}", name));
}

/**
 * @brief 判断是否可以部署指定的 Ant
 *
 * @param gameState 当前的游戏状态
 * @param name Ant 的名称
 * @return 若可以部署，则返回 `true`；否则返回 `false`。
 */
bool AntFactory::canDeployAnt(GameState &gameState, const string &name) const {
    if (name == "QueenAnt") {
        if (queenAnt == nullptr) {
            return true;
        }
        return false;
    } else {
        auto it = antCosts.find(name);
        if (it != antCosts.end()) {
            return it->second <= gameState.food;
        }
    }

    return false;
}

/**
 * @brief 创建一个 Ant
 *
 * @param name Ant 的名称
 * @return 创建的 Ant
 */
Ant *AntFactory::createAnt(const string &name) const {
    if (name == "QueenAnt") { // 针对 QueenAnt 的特殊处理
        if (queenAnt == nullptr) {
            queenAnt = new QueenAnt();
            log(LOGTEST, "Created QueenAnt");
            return queenAnt;
        }
        log(LOGTEST, "QueenAnt has already been created");
        return nullptr;
    } else {
        auto it = antConstructors.find(name);
        if (it != antConstructors.end()) {
            log(LOGTEST, format("Creating Ant: {}", name));
            return it->second();
        }
    }
    log(LOGERROR, format("Ant constructor {} not found", name));
    return nullptr;
}

/**
 * @brief 获取所有 Ant 的名称
 *
 * @return 所有 Ant 的名称
 */
vector<string> AntFactory::getAntNames() const {
    vector<string> names;
    for (const auto &pair : antConstructors) {
        names.push_back(pair.first);
    }
    return names;
}

/**
 * @brief 注册一个 Ant 类
 *
 * @param AntClass Ant 类名
 */
#define REGISTER_ANT_CLASS(AntClass, FoodCost)                                  \
    class AntClass##Register {                                                  \
    public:                                                                     \
        AntClass##Register() {                                                  \
            AntFactory::getInstance().registerAnt(                              \
                #AntClass, []() -> Ant * { return new AntClass(); }, FoodCost); \
        }                                                                       \
    };                                                                          \
    static const AntClass##Register global_##AntClass##Register;

REGISTER_ANT_CLASS(AntRemover, 0)
REGISTER_ANT_CLASS(BodyguardAnt, 4)
REGISTER_ANT_CLASS(FireAnt, 5)
REGISTER_ANT_CLASS(HarvestAnt, 2)
REGISTER_ANT_CLASS(HungryAnt, 4)
REGISTER_ANT_CLASS(LaserAnt, 10)
REGISTER_ANT_CLASS(LongThrower, 2)
REGISTER_ANT_CLASS(NinjaAnt, 5)
REGISTER_ANT_CLASS(QueenAnt, 7)
REGISTER_ANT_CLASS(ScaryThrower, 6)
REGISTER_ANT_CLASS(ScubaThrower, 6)
REGISTER_ANT_CLASS(ShortThrower, 2)
REGISTER_ANT_CLASS(SlowThrower, 4)
REGISTER_ANT_CLASS(TankAnt, 6)
REGISTER_ANT_CLASS(ThrowerAnt, 3)
REGISTER_ANT_CLASS(WallAnt, 4)
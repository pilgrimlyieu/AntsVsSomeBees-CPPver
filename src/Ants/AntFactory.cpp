#include "AntFactory.hpp"
#include "AntRemover.hpp"
#include "BodyguardAnt.hpp"
#include "FireAnt.hpp"
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
 * @brief 注册一个 Ant 类
 *
 * @param name Ant 的名称
 * @param constructor 一个函数，返回一个新的 Ant
 */
void AntFactory::registerAnt(const string &name, ant_constructor constructor) {
    antConstructors[name] = constructor;
    log(LOGTEST, format("Registered Ant: {}", name));
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
#define REGISTER_ANT_CLASS(AntClass)                                                         \
    class AntClass##Register {                                                               \
    public:                                                                                  \
        AntClass##Register() {                                                               \
            AntFactory::getInstance().registerAnt(#AntClass,                                 \
                                                  []() -> Ant * { return new AntClass(); }); \
        }                                                                                    \
    };                                                                                       \
    static const AntClass##Register global_##AntClass##Register;

REGISTER_ANT_CLASS(Ant)
REGISTER_ANT_CLASS(AntRemover)
REGISTER_ANT_CLASS(BodyguardAnt)
REGISTER_ANT_CLASS(FireAnt)
REGISTER_ANT_CLASS(HarvestAnt)
REGISTER_ANT_CLASS(HungryAnt)
REGISTER_ANT_CLASS(LaserAnt)
REGISTER_ANT_CLASS(LongThrower)
REGISTER_ANT_CLASS(NinjaAnt)
REGISTER_ANT_CLASS(QueenAnt)
REGISTER_ANT_CLASS(ScaryThrower)
REGISTER_ANT_CLASS(ScubaThrower)
REGISTER_ANT_CLASS(ShortThrower)
REGISTER_ANT_CLASS(SlowThrower)
REGISTER_ANT_CLASS(TankAnt)
REGISTER_ANT_CLASS(ThrowerAnt)
REGISTER_ANT_CLASS(WallAnt)
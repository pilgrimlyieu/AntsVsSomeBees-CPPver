#include "GameState.hpp"
#include "Ant.hpp"
#include "AntFactory.hpp"
#include "AntsLoseException.hpp"
#include "AntsWinException.hpp"
#include "Bee.hpp"
#include "Utilities.hpp"
#include "Water.hpp"

/**
 * @brief 构造一个新的 GameState
 *
 * @param antFactory Ant 工厂
 * @param beehive beehive
 * @param createPlaces 创建地点的函数
 * @param dimensions 地图尺寸
 * @param food 初始食物余额，默认为 2
 */
GameState::GameState(Hive *beehive, create_places createPlaces, dim dimensions, int food)
    : beehive(beehive), dimensions(std::move(dimensions)), antFactory(&AntFactory::getInstance()),
      food(food) {
    configure(beehive, createPlaces);
}

/**
 * @brief 配置 GameState
 *
 * 配置 GameState ，包括创建 Ant Home Base、地点、beehive 和 Bee 入口。
 *
 * @param beehive 蜂巢
 * @param createPlaces 创建地点的函数
 */
void GameState::configure(Hive *beehive, create_places createPlaces) {
    base = new AntHomeBase("Ant Home Base");
    places.clear();
    bee_entrances.clear();
    auto register_place = [this, beehive](Place *place, bool isBeeEntrance) {
        places[place->name] = place;
        log(LOGTEST, format("Adding {}", *place));
        if (isBeeEntrance) {
            place->entrance = beehive;
            bee_entrances.push_back(place);
        }
    };
    register_place(beehive, false);
    createPlaces(base, register_place, dimensions);
}

/**
 * @brief Ant 执行动作
 */
void GameState::antsTakeActions() {
    for (auto ant : getAnts()) {
        if (ant->health > 0) {
            ant->action(*this);
        }
    }
}

/**
 * @brief Bee 执行动作
 */
void GameState::beesTakeActions() {
    bees_list beesCurrent(activeBees);
    for (auto bee : beesCurrent) {
        if (bee->health > 0) {
            bee->action(*this);
        }
        if (bee->health <= 0) {
            numBees--;
            log(LOGINFO, format("Bee {} is dead", string(*bee)));
            activeBees.erase(std::remove(activeBees.begin(), activeBees.end(), bee),
                             activeBees.end());
        }
    }
    if (numBees == 0) {
        antsWin();
    }
}

/**
 * @brief 模拟游戏
 *
 * 模拟游戏，直到 Ant 获胜或失败。
 *
 * @return 若 Ant 获胜则返回 `true` ，否则返回 `false` 。
 */
Simulator GameState::simulate() {
    bool result;
    numBees = getBees().size();
    log(LOGINFO, format("Simulation started with {} bees", numBees));
    try {
        while (true) {
            log(LOGTEST, *this);
            log(LOGTEST, format("{} bees remaining", numBees));
            beehive->strategy(*this);
            co_yield nullptr;
            antsTakeActions();
            time++;
            co_yield nullptr;
            beesTakeActions();
        }
    } catch (AntsWinException &e) {
        log(LOGINFO, "All bees are vanquished. You win!");
        result = true;
    } catch (AntsLoseException &e) {
        log(LOGINFO, "The bees reached homebase or the queen ant has perished. Please try again.");
        result = false;
    } catch (exception &e) {
        log(LOGERROR, e.what());
        result = false;
    }
    co_yield result;
}

/**
 * @brief 部署一个 Ant
 *
 * 部署一个 Ant ，若食物不足则返回 `nullptr` 。
 *
 * @param placeName 地点名称
 * @param antTypeName Ant 类型名称
 * @return 部署的 Ant
 */
Ant *GameState::deployAnt(string placeName, string antTypeName) {
    Ant *ant = antFactory->createAnt(antTypeName);
    if (ant != nullptr) {
        if (ant->getFoodCost() > food) {
            delete ant;
            log(LOGERROR, format("Insufficient food to deploy {0}.", antTypeName));
            return nullptr;
        }
        log(LOGTEST, format("Deploying {0} to {1}", antTypeName, placeName));
        places[placeName]->addInsect(ant);
        food -= ant->getFoodCost();
    }
    return ant;
}

/**
 * @brief 移除一个 Ant
 *
 * @param placeName 地点名称
 */
void GameState::removeAnt(string placeName) {
    Place *place = places[placeName];
    if (place->ant != nullptr) {
        place->removeInsect(place->ant);
    }
}

/**
 * @brief 获取所有的 Ant
 *
 * @return 所有的 Ant
 */
GameState::ants_list GameState::getAnts() const {
    ants_list ants;
    for (auto &[name, place] : places) {
        if (place->ant != nullptr) {
            ants.push_back(place->ant);
        }
    }
    return ants;
}

/**
 * @brief 获取所有的 Bee
 *
 * @return 所有的 Bee
 */
bees_list GameState::getBees() const {
    bees_list bees;
    for (auto &[name, place] : places) {
        for (auto bee : place->bees) {
            bees.push_back(bee);
        }
    }
    return bees;
}

/**
 * @brief 获取所有的 Insect
 *
 * @return 所有的 Insect
 */
GameState::insects_list GameState::getInsects() const {
    insects_list insects;
    ants_list ants = getAnts();
    bees_list bees = getBees();
    insects.insert(insects.end(), ants.begin(), ants.end());
    insects.insert(insects.end(), bees.begin(), bees.end());
    return insects;
}

/**
 * @brief 将 GameState 转换为字符串表示形式
 *
 * 将 GameState 转换为字符串表示形式，格式为 "[Insect1, Insect2, ...] (Food: x, Time: y)"。
 *
 * @return GameState 的字符串表示形式
 */
GameState::operator string() const {
    string status = format(" (Food: {0}, Time: {1})", food, time);
    string result = "[\n\t";
    insects_list insects = getInsects();
    for (size_t i = 0; i < insects.size(); ++i) {
        result += string(*insects[i]);
        if (i != insects.size() - 1) {
            result += ";\t";
        }
        if (i % 5 == 4) { // 每行显示 5 个 Insect
            result += "\n\t";
        }
    }
    result += "\n]" + status;
    return result;
}

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

/**
 * @brief 创建布局
 *
 * 从基地开始，创建一系列的 Tunnel，其中每隔一定距离会有湿地。
 *
 * 具体而言，当 `moatFrequency` 不为 0 时，每隔 `moatFrequency` 步会有一个湿地。
 *
 * @param base 基地
 * @param registerPlace 注册 Place 的函数
 * @param dimensions 布局维度
 * @param moatFrequency 湿地频率
 */
void GameState::createLayout(AntHomeBase *base, register_place_f registerPlace, dim dimensions,
                             int moatFrequency) {
    int tunnels = dimensions.first;
    int length = dimensions.second;
    for (int tunnel = 0; tunnel < tunnels; tunnel++) {
        Place *exit = base;
        for (int step = 0; step < length; step++) {
            if (moatFrequency != 0 && (step + 1) % moatFrequency == 0) {
                exit = new Water(format("Water_{}_{}", tunnel, step), exit);
            } else {
                exit = new Place(format("Tunnel_{}_{}", tunnel, step), exit);
            }
            registerPlace(exit, step == length - 1);
        }
    }
}

/**
 * @brief 湿地布局
 *
 * 从基地开始，创建一系列的 Tunnel，其中每隔一定距离会有湿地。
 *
 * @param base 基地
 * @param registerPlace 注册 Place 的函数
 * @param dimensions 布局维度
 */
void wetLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions) {
    GameState::createLayout(base, registerPlace, dimensions, 3);
}

/**
 * @brief 干地布局
 *
 * 从基地开始，创建一系列的 Tunnel。
 *
 * @param base 基地
 * @param registerPlace 注册 Place 的函数
 * @param dimensions 布局维度
 */
void dryLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions) {
    GameState::createLayout(base, registerPlace, dimensions, 0);
}

#include "GameState.h"
#include "Ant.h"
#include "AntFactory.h"
#include "AntsLoseException.h"
#include "AntsWinException.h"
#include "Bee.h"
#include "Utilities.h"
#include "Water.h"

/**
 * @brief 构造一个新的 GameState
 *
 * @param strategy 游戏策略
 * @param antFactory Ant 工厂
 * @param beehive beehive
 * @param createPlaces 创建地点的函数
 * @param dimensions 地图尺寸
 * @param food 初始食物余额，默认为 2
 */
GameState::GameState(strat strategy, AntFactory *antFactory, Hive *beehive,
                     create_places createPlaces, dim dimensions, int food)
    : strategy(strategy), beehive(beehive), dimensions(std::move(dimensions)),
      antFactory(antFactory) {
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
        if (isBeeEntrance) {
            place->entrance = beehive;
            bee_entrances.push_back(place);
        }
    };
    register_place(beehive, false);
    createPlaces(base, register_place, dimensions);
}

/**
 * @brief 模拟游戏
 *
 * 模拟游戏，直到 Ant 获胜或失败。
 *
 * @return 若 Ant 获胜则返回 `true` ，否则返回 `false` 。
 */
bool GameState::simulate() {
    try {
        while (true) {
            beehive->strategy(*this);
            strategy(*this);
            for (auto ant : getAnts()) {
                if (ant->health > 0) {
                    ant->action(*this);
                }
            }
            bees_list beesCurrent(activeBees);
            for (auto bee : beesCurrent) {
                if (bee->health > 0) {
                    bee->action(*this);
                }
                if (bee->health <= 0) {
                    activeBees.erase(std::remove(activeBees.begin(), activeBees.end(), bee),
                                     activeBees.end());
                }
            }
            if (activeBees.empty()) {
                antsWin();
            }
            time++;
        }
    } catch (AntsWinException &e) {
        log(LOGINFO, "All bees are vanquished. You win!");
        return true;
    } catch (AntsLoseException &e) {
        log(LOGINFO, "The ant queen has perished. Please try again.");
        return false;
    } catch (exception &e) {
        log(LOGERROR, e.what());
        return false;
    }
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
        if (ant->foodCost > food) {
            delete ant;
            return nullptr;
        }
        places[placeName]->addInsect(ant);
        food -= ant->foodCost;
    }
    return ant;
}

/**
 * @brief 移除一个 Ant
 *
 * 移除一个 Ant 。
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
 * 获取所有的 Ant 。
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
 * 获取所有的 Bee 。
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
 * 获取所有的 Insect 。
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
    string result = "[";
    insects_list insects = getInsects();
    for (size_t i = 0; i < insects.size(); ++i) {
        result += string(*insects[i]);
        if (i != insects.size() - 1) {
            result += ", ";
        }
        if (i % 5 == 4) { // 每行显示 5 个 Insect
            result += "\n";
        }
    }
    result += "]" + status;
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
 * @brief 湿地布局
 *
 * 从基地开始，创建一系列的隧道，其中每隔一定距离会有湿地。
 *
 * 具体而言，当 `moatFrequency` 不为 0 时，每隔 `moatFrequency` 步会有一个湿地。
 *
 * @param base 基地
 * @param registerPlace 注册 Place 的函数
 * @param tunnels 隧道数量
 * @param length 隧道长度
 * @param moatFrequency 湿地频率
 */
void wetLayout(Place *base, GameState::register_place_f registerPlace, int tunnels, int length,
               int moatFrequency) {
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
 * @brief 干地布局
 *
 * 从基地开始，创建一系列的隧道。
 *
 * @param base 基地
 * @param registerPlace 注册 Place 的函数
 * @param tunnels 隧道数量
 * @param length 隧道长度
 */
void dryLayout(Place *base, GameState::register_place_f registerPlace, int tunnels, int length) {
    wetLayout(base, registerPlace, tunnels, length, 0);
}
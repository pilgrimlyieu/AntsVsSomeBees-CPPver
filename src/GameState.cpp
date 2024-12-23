#include "GameState.h"
#include "Ant.h"
#include "AntFactory.h"
#include "AntsLoseException.h"
#include "AntsWinException.h"
#include "Bee.h"
#include "Insect.h"
#include "Utilities.h"

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
    : strategy(strategy), beehive(beehive), dimensions(dimensions), antFactory(antFactory) {
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
            for (auto it = activeBees.begin(); it != activeBees.end();) {
                Bee *bee = *it;
                if (bee->health > 0) {
                    bee->action(*this);
                    it++;
                }
                if (bee->health <= 0) {
                    it = activeBees.erase(it);
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

void GameState::removeAnt(string placeName) {
    Place *place = places[placeName];
    if (place->ant != nullptr) {
        place->removeInsect(place->ant);
    }
}

vector<Ant *> GameState::getAnts() const {
    vector<Ant *> ants;
    for (auto &[name, place] : places) {
        if (place->ant != nullptr) {
            ants.push_back(place->ant);
        }
    }
    return ants;
}

vector<Bee *> GameState::getBees() const {
    vector<Bee *> bees;
    for (auto &[name, place] : places) {
        for (auto bee : place->bees) {
            bees.push_back(bee);
        }
    }
    return bees;
}

vector<Insect *> GameState::getInsects() const {
    vector<Insect *> insects;
    vector<Ant *> ants = getAnts();
    vector<Bee *> bees = getBees();
    insects.insert(insects.end(), ants.begin(), ants.end());
    insects.insert(insects.end(), bees.begin(), bees.end());
    return insects;
}

GameState::operator string() const {
    string status = format(" (Food: {0}, Time: {1})", food, time);
    string result = "[";
    vector<Insect *> insects = getInsects();
    for (size_t i = 0; i < insects.size(); ++i) {
        result += string(*insects[i]);
        if (i != insects.size() - 1) {
            result += ", ";
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
#include "GameState.hpp"
#include "Ant.hpp"
#include "AntFactory.hpp"
#include "AntsLoseException.hpp"
#include "AntsWinException.hpp"
#include "Bee.hpp"
#include "ContainerAnt.hpp"
#include "Version.hpp"
#include "Water.hpp"

AntFactory *GameState::antFactory = &AntFactory::getInstance();

/**
 * @brief 创建一个 GameState
 *
 * @param food 初始食物余额，默认为 2
 * @param dimensions 地图尺寸
 */
GameState::GameState(int food, dim dimensions)
    : food(food), beehive(nullptr), dimensions(std::move(dimensions)) {}

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
    : food(food), beehive(beehive), dimensions(std::move(dimensions)) {
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
        log(LOGTEST, format("Adding {}", place));
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
        if (ant->health <= 0) {
            delete ant;
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
            activeBees.erase(std::remove(activeBees.begin(), activeBees.end(), bee),
                             activeBees.end());
            delete bee;
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
        result = true;
    } catch (AntsLoseException &e) {
        result = false;
    } catch (exception &e) {
        log(LOGERROR, e.what());
        result = false;
    }
    log(LOGTEST, *this);
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
    if (!AntFactory::getInstance().canDeployAnt(*this, antTypeName)) {
        log(LOGERROR, format("Can not deploy {0}.", antTypeName));
        return nullptr;
    }
    if (places.find(placeName) == places.end()) {
        throw out_of_range(format("Place {0} not found", placeName));
    }
    Ant *ant = antFactory->createAnt(antTypeName);
    if (ant != nullptr) {
        log(LOGTEST, format("Deploying {0} to {1}", antTypeName, placeName));
        places[placeName]->addInsect(ant);
        food -= ant->getFoodCost();
    }
    if (ant->getName() == "AntRemover") {
        delete ant;
        ant = nullptr;
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
            auto container_ptr = dynamic_cast<ContainerAnt *>(place->ant);
            if (container_ptr && container_ptr->antContained != nullptr) {
                ants.push_back(container_ptr->antContained);
            }
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
        if (i % 3 == 2) { // 每行显示 3 个 Insect
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
    log(LOGINFO, "All bees are vanquished. You win!");
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
    log(LOGINFO, "The bees reached homebase or the queen ant has perished. Please try again.");
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

/**
 * @brief 序列化当前 GameState
 *
 * @return 当前 GameState 的序列化 JSON 对象。
 */
json GameState::serialize() const {
    json j;
    j["version"] = VERSION;
    j["time"] = time;
    j["food"] = food;
    j["numBees"] = numBees;
    j["dimensions"] = {dimensions.first, dimensions.second};

    j["places"] = json::array();
    for (const auto &[name, place] : places) {
        j["places"].push_back({
            {"name",  name              },
            {"place", place->serialize()}
        });
    }

    j["bee_entrances"] = json::array();
    for (const auto &entrance : bee_entrances) {
        j["bee_entrances"].push_back(entrance->name);
    }

    return j;
}

/**
 * @brief 从 JSON 对象反序列化得到 GameState
 *
 * @param data GameState 的 JSON 对象
 * @return 反序列化后的 GameState
 */
GameState GameState::deserialize(const json &data) {
    auto state = GameState(data["food"], {data["dimensions"][0], data["dimensions"][1]});
    string version = data["version"];
    if (version != VERSION) {
        log(LOGERROR, format("Version mismatch: {0} != {1}, which may cause issues. Go to "
                             "{2}/releases/tag/v{0} for the matching version.",
                             version, VERSION, AVSBInfo::REPOSITORY));
    }
    state.time = data["time"];
    state.numBees = data["numBees"];
    state.base = new AntHomeBase("Ant Home Base");
    state.places["Ant Home Base"] = state.base;

    for (const auto &placeData : data["places"]) {
        const string &name = placeData["name"];
        const json &place_json = placeData["place"];
        Place *place = Place::deserialize(place_json);
        if (place->name == "Hive") {
            state.beehive = dynamic_cast<Hive *>(place);
        }
        state.places[name] = place;
    }

    for (const auto &placeData : data["places"]) {
        const string &name = placeData["name"];
        const json &place_json = placeData["place"];
        Place *current = state.places[name];
        if (place_json.contains("exit_name") && !place_json["exit_name"].empty()) {
            if (state.places.contains(place_json["exit_name"])) {
                current->exit = state.places[place_json["exit_name"]];
            } else {
                current->exit = nullptr;
            }
        }
        if (place_json.contains("entrance_name") && !place_json["entrance_name"].empty()) {
            if (state.places.contains(place_json["entrance_name"])) {
                current->entrance = state.places[place_json["entrance_name"]];
            } else {
                current->entrance = nullptr;
            }
        }
    }

    for (const auto &entrance_name : data["bee_entrances"]) {
        state.bee_entrances.push_back(state.places[entrance_name]);
    }

    for (const auto &[name, place] : state.places) {
        if (!place->getIsHive()) {
            for (Bee *bee : place->bees) {
                state.activeBees.push_back(bee);
            }
        }
    }

    return state;
}
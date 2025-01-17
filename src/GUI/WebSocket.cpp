#include "WebSocket.hpp"
#include "Bee.hpp"

/**
 * @brief 获取事件发射器
 */
EventEmitter &WebSocket::getEmitter() {
    return emitter;
}

/**
 * @brief 设置事件发射器
 *
 * 设置事件发射器。
 *
 * @param emitter 事件发射器
 */
void WebSocket::setEmitter(EventEmitter emitter) {
    WebSocket::emitter = std::move(emitter);
}

/**
 * @brief 当 Bee 移动时调用
 *
 * 当 Bee 移动时调用，向前端发送移动事件。
 *
 * @param bee 移动的 Bee
 * @param place 目的地
 */
void WebSocket::onInsectMove(Bee *bee, Place *place) {
    if (bee->getPlace() && place->name == "Ant Home Base") {
        return;
    }
    if (bee->getPlace() && bee->getPlace()->getIsHive()) {
        crow::json::wvalue data;
        data["bee_id"] = bee->getId();
        data["bee_name"] = bee->getName();
        data["destination"] = parseCoordinates(place->name);
        emitter.emit("moveBeeFromHive", data);
    } else {
        crow::json::wvalue data;
        data["bee_id"] = bee->getId();
        data["destination"] = parseCoordinates(place->name);
        data["current_pos"] = parseCoordinates(bee->getPlace()->name);
        emitter.emit("moveBee", data);
    }
}

/**
 * @brief 当 ThrowerAnt 攻击时调用
 *
 * 当 ThrowerAnt 攻击时调用，向前端发送攻击事件。
 *
 * @param thrower 攻击的 ThrowerAnt
 * @param target 攻击的目标
 */
void WebSocket::onThrowerAttack(const ThrowerAnt *thrower, const Bee *target) {
    if (target) {
        crow::json::wvalue data;
        data["target_pos"] = parseCoordinates(target->getPlace()->name);
        data["thrower_pos"] = parseCoordinates(thrower->getPlace()->name);
        emitter.emit("throwAt", data);
    }
}

/**
 * @brief 当生命值减少时调用
 *
 * 当生命值减少时调用，向前端发送生命值减少事件。
 *
 * @param insect 生命值减少的 Insect
 */
void WebSocket::onHealthReduced(const Insect *insect) {
    crow::json::wvalue data;
    data["insect_id"] = insect->getId();
    emitter.emit("reduceHealth", data);
}

/**
 * @brief 当 Insect 死亡时调用
 *
 * 当 Insect 死亡时调用，向前端发送死亡事件。
 *
 * @param insect 死亡的 Insect
 */
void WebSocket::onInsectDeath(const Insect *insect) {
    crow::json::wvalue data;
    data["insect_id"] = insect->getId();
    emitter.emit("onInsectDeath", data);
}

/**
 * @brief 解析坐标
 *
 * 从地点名称中解析出坐标。
 *
 * @param name 地点名称
 * @return 坐标
 */
vector<int> parseCoordinates(const string &name) {
    size_t first = name.find("_");
    size_t second = name.find("_", first + 1);
    assert(first != string::npos && second != string::npos);
    int x = stoi(name.substr(first + 1, second - first - 1));
    int y = stoi(name.substr(second + 1));
    return {x, y};
}
/**
 * @file Utilities.h
 * @brief 提供一些常用的工具函数和类型定义。
 */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

// #ifdef DEBUG
// #define private   public
// #define protected public
// #endif

#include <coroutine>
#include <cstdarg>
#include <format>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "ProjectConfig.hpp"
#include "ProjectInfo.hpp"


class CLI;
class GameState;
class Place;
class Insect;
class Ant;
class Bee;

struct CLIConfig;

#ifdef DEBUG
#define THROW_EXCEPTION(Ex, msg)                                        \
    do {                                                                \
        log(LOGERROR, msg);                                             \
        throw Ex(std::format("[[{}:{}]] {}", __FILE__, __LINE__, msg)); \
    } while (0)
#else
#define THROW_EXCEPTION(Ex, msg) \
    do {                         \
        log(LOGERROR, msg);      \
        throw Ex(msg);           \
    } while (0)
#endif

using std::exception;
using std::format;
using std::function;
using std::invalid_argument;
using std::make_shared;
using std::make_unique;
using std::map;
using std::nullopt;
using std::optional;
using std::out_of_range;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using g_time = int;
static const g_time TIME_START = (g_time)0;

using bee_type = function<Bee *(double)>;
using bees_list = vector<Bee *>;
using places_list = vector<Place *>;

/**
 * @brief 游戏策略
 *
 * 接受 GameState 的引用，执行游戏策略。
 */
using strat = void (*)(GameState &);

/**
 * @brief 维度
 */
using dim = pair<int, int>;

/**
 * @brief 日志级别
 *
 * - LOGINFO: 信息
 *
 * - LOGERROR: 错误
 *
 * - LOGTEST: 测试
 */
enum class LogLevel {
    LOGINFO,
    LOGERROR,
    LOGTEST,
};
using enum LogLevel;

void gameInit();

void log(LogLevel level, const string &msg);

vector<string> split(const string &str, char delim);

/**
 * @brief 从列表中随机选择一个元素。
 *
 * 该函数从提供的列表 `list` 中随机选择一个元素并返回。
 *
 * @tparam T `list` 元素的类型。
 * @param list 要选择元素的列表。
 * @return T 类型的元素，若列表为空则返回 `nullptr`。
 */
template <typename T> T randomElement(const vector<T> &list) {
    if (list.size() == 0) {
        return nullptr;
    }
    return list[rand() % list.size()];
}

#endif // UTILITIES_HPP
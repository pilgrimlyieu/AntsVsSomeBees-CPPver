#ifndef PROJECTDECLARATIONS_HPP
#define PROJECTDECLARATIONS_HPP

#include "Libraries.hpp"

class CLI;
class GameState;
class Place;
class Insect;
class Ant;
class Bee;

struct CLIConfig;

using g_time = int;

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
 * - LOGTEST: 测试
 *
 * - LOGINFO: 信息
 *
 * - LOGERROR: 错误
 *
 * - NOLOG: 无日志
 */
enum class LogLevel {
    LOGTEST,
    LOGINFO,
    LOGERROR,
    NOLOG,
};
using enum LogLevel;

#endif // PROJECTDECLARATIONS_HPP
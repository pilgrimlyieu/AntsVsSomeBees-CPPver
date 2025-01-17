/**
 * @file Utilities.h
 * @brief 提供一些常用的工具。
 */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Config.hpp"
#include "Info.hpp"

// #ifdef DEBUG
// #define private   public
// #define protected public
// #endif

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
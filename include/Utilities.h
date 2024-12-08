#ifndef UTILITIES_H
#define UTILITIES_H

#if defined(DEBUG) || defined(TEST)
#define private   public
#define protected public
#endif

#include <cstdarg>
#include <format>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

class GameState;
class Place;
class Insect;
class Ant;
class Bee;

using g_time = int;
#define TIME_START (g_time)0

using bee_t = std::function<Bee *(int)>;
using bee_list = std::vector<Bee *>;

/**
 * @brief 获取列表中指定索引处的元素。
 *
 * 该函数从提供的列表 `list` 中返回给定索引 `index` 处的元素。
 *
 * @tparam T `list` 元素的类型。
 * @param list 要检索元素的列表。
 * @param index 要检索的元素的索引，从 0 开始。
 * @return T 类型的元素。
 *
 * @throws std::out_of_range 若索引超出范围。
 *
 * @example
 * @code
 * std::list<int> myList = {1, 2, 3, 4, 5};
 * int value = get(myList, 2); // value = 3
 * @endcode
 */
template <class T> T get(const std::list<T> &list, int index) {
    if (index < 0 || index >= list.size()) {
        throw std::out_of_range("索引超出范围");
    }
    auto it = list.begin();
    advance(it, index);
    return *it;
}

#endif // UTILITIES_H
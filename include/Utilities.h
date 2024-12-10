#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef DEBUG
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

#ifdef DEBUG
#define THROW_EXCEPTION(ex, msg) throw ex(std::format("[[{}:{}]] {}", __FILE__, __LINE__, msg))
#else
#define THROW_EXCEPTION(ex, msg) throw ex(msg)
#endif

using std::exception;
using std::format;
using std::function;
using std::invalid_argument;
using std::list;
using std::make_shared;
using std::make_unique;
using std::map;
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
using bee_list = vector<Bee *>;

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
 * @brief 获取列表中指定索引处的元素。
 *
 * 该函数从提供的列表 `list` 中返回给定索引 `index` 处的元素。
 *
 * @tparam T `list` 元素的类型。
 * @param list 要检索元素的列表。
 * @param index 要检索的元素的索引，从 0 开始。
 * @return T 类型的元素。
 *
 * @throws out_of_range 若索引超出范围。
 *
 * @example
 * @code
 * list<int> myList = {1, 2, 3, 4, 5};
 * int value = get(myList, 2); // value = 3
 * @endcode
 */
template <class T> T get(const list<T> &list, int index) {
    if (index < 0 || index >= list.size()) {
        THROW_EXCEPTION(out_of_range,
                        format("Index {} out of range 0..{}", index, list.size() - 1));
    }
    auto it = list.begin();
    advance(it, index);
    return *it;
}

#endif // UTILITIES_H
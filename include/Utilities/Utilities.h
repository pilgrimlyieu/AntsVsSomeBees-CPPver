#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdarg>
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

using Bee_t = std::function<Bee *(int)>;

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

/**
 * @brief 类 `printf` 的字符串格式化函数
 *
 * 该函数接受一个格式化字符串和一个可变数量的参数，
 * 根据格式化说明符格式化字符串，并返回格式化后的字符串。
 *
 * @remark 引自 https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * @tparam Args 可变模板参数包，表示参数的类型。
 * @param format 包含格式说明符的格式化字符串。
 * @param args 用于格式化的参数。
 * @return 格式化后的字符串。
 * @throws std::runtime_error 若在格式化过程中发生错误。
 */
template <typename... Args> std::string string_format(const std::string &format, Args... args) {
    int size_s = snprintf(nullptr, 0, format.c_str(), args...) + 1;
    if (size_s <= 0) {
        throw std::runtime_error("格式化字符串失败");
    }
    size_t size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

bool isBee(Bee_t beeType, Insect *insect);

#endif // UTILITIES_H
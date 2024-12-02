#ifndef UTILITIES_H
#define UTILITIES_H

#include "TypeDefinition.h"
#include <cstdarg>
#include <list>
#include <stdexcept>
#include <vector>

using namespace std;

class GameState;
class Place;
class Insect;
class Ant;
class Bee;

/**
 * @brief Retrieves an element from a list at the specified index.
 *
 * This function returns the element at the given index from the provided list.
 *
 * @tparam T The type of elements in the list.
 * @param list The list from which to retrieve the element.
 * @param index The zero-based index of the element to retrieve.
 * @return T The element at the specified index.
 *
 * @throws std::out_of_range if the index is out of the bounds of the list.
 *
 * @example
 * @code
 * std::list<int> myList = {1, 2, 3, 4, 5};
 * int value = get(myList, 2); // value will be 3
 * @endcode
 */
template <class T> T get(const list<T> &list, int index) {
    auto it = list.begin();
    advance(it, index);
    return *it;
}

string format(const string &fmt, ...);

#endif // UTILITIES_H
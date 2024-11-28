#ifndef UTILITIES_H
#define UTILITIES_H

#include "TypeDefinition.h"
#include <list>
#include <stdexcept>
#include <vector>

using namespace std;

class GameState;
class Place;
class Insect;
class Ant;
class Bee;

template <class T> T get(const list<T> &list, int index) {
    auto it = list.begin();
    advance(it, index);
    return *it;
}

#endif // UTILITIES_H
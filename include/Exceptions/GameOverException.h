#ifndef GAMEOVEREXCEPTION_H
#define GAMEOVEREXCEPTION_H

#include "Utilities.h"

class GameOverException : public std::exception {
public:
    GameOverException() = default;
};

#endif // GAMEOVEREXCEPTION_H
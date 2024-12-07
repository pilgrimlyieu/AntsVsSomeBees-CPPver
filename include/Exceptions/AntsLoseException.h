#ifndef ANTSLOSEEXCEPTION_H
#define ANTSLOSEEXCEPTION_H

#include "GameOverException.h"

class AntsLoseException final : public GameOverException {
public:
    AntsLoseException() = default;
};

#endif // ANTSLOSEEXCEPTION_H
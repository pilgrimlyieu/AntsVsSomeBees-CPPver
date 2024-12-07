#ifndef ANTSWINEXCEPTION_H
#define ANTSWINEXCEPTION_H

#include "GameOverException.h"

class AntsWinException final : public GameOverException {
public:
    AntsWinException() = default;
};

#endif // ANTSWINEXCEPTION_H
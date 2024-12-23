#include "Utilities.h"
#include <iostream>

/**
 * @brief 游戏初始化
 */
void gameInit() {
    srand((unsigned)time(NULL));
}

/**
 * @brief 记录日志
 *
 * @param msg 日志信息
 */
void log(LogLevel level, const string &msg) {
    static const string ANSI_RESET = "\x1B[0m";
    static const string ANSI_BLUE = "\x1B[34m";
    static const string ANSI_RED = "\x1B[31m";
    static const string ANSI_YELLOW = "\x1B[33m";

    switch (level) {
    case LOGINFO:
        std::cout << ANSI_BLUE << "[INFO] " << msg << ANSI_RESET << std::endl;
        break;
    case LOGERROR:
        std::cerr << ANSI_RED << "[ERROR] " << msg << ANSI_RESET << std::endl;
        break;
    case LOGTEST:
        std::cout << ANSI_YELLOW << "[TEST] " << msg << ANSI_RESET << std::endl;
        break;
    }
}
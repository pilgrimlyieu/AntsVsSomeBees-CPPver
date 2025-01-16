#include "Utilities.hpp"
#include <iostream>

/**
 * @brief 游戏初始化
 */
void gameInit() {
    srand((unsigned)time(nullptr));
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
#ifdef DEBUG
        std::cout << ANSI_YELLOW << "[TEST] " << msg << ANSI_RESET << std::endl;
#endif
        break;
    }
}

/**
 * @brief 分割字符串
 *
 * @param str 要分割的字符串
 * @param delim 分隔符
 * @return 分割后的字符串列表
 */
vector<string> split(const string &str, char delim) {
    vector<string> parts;
    size_t start = 0;
    size_t end = str.find(delim);
    while (end != string::npos) {
        parts.emplace_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delim, start);
    }
    parts.emplace_back(str.substr(start));
    return parts;
}
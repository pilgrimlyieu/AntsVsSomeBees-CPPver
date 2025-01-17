#include "Utilities.hpp"
#include "CLI.hpp"

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
    LogLevel cfgLogLevel = ConfigManager::getConfig().getLogLevel();
    if (level == LOGTEST && cfgLogLevel <= LOGTEST) {
        std::cout << ANSI_YELLOW << "[TEST] " << ANSI_RESET << msg << std::endl;
    } else if (level == LOGINFO && cfgLogLevel <= LOGINFO) {
        std::cout << ANSI_BLUE << "[INFO] " << ANSI_RESET << msg << std::endl;
    } else if (level == LOGERROR && cfgLogLevel <= LOGERROR) {
        std::cerr << ANSI_RED << "[ERROR] " << ANSI_RESET << msg << std::endl;
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
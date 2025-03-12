#include "Utilities.hpp"
#include "CLI.hpp"

/**
 * @brief 程序初始化
 */
void programInit() {
#ifdef _WIN32
    // Windows: Get the full path of the executable and set the working directory to its parent
    // directory.
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    std::filesystem::current_path(std::filesystem::path(exePath).parent_path());
#elif __APPLE__
    // macOS: Use _NSGetExecutablePath to get the full path of the executable.
    char exePath[PATH_MAX];
    uint32_t size = sizeof(exePath);
    if (_NSGetExecutablePath(exePath, &size) == 0) {
        std::filesystem::current_path(std::filesystem::path(exePath).parent_path());
    }
#elif __linux__
    // Linux: Read the symbolic link /proc/self/exe to get the full path of the executable.
    char exePath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (count != -1) {
        exePath[count] = '\0';
        std::filesystem::current_path(std::filesystem::path(exePath).parent_path());
    }
#endif
}

/**
 * @brief 游戏初始化
 */
void gameInit() {
    srand(static_cast<unsigned>(time(nullptr)));
}

/**
 * @brief 记录日志
 *
 * @param level 日志等级
 * @param msg 日志信息
 * @param force 是否强制显示
 */
void log(LogLevel level, const string &msg, bool force) {
    LogLevel logLevel;
    if (!force) {
        logLevel = ConfigManager::getConfig().getLogLevel();
    } else {
        logLevel = LOGTEST;
    }
    if (level == LOGTEST && logLevel <= LOGTEST) {
        std::cout << ANSI_YELLOW << "[TEST] " << ANSI_RESET << msg << std::endl;
    } else if (level == LOGINFO && logLevel <= LOGINFO) {
        std::cout << ANSI_BLUE << "[INFO] " << ANSI_RESET << msg << std::endl;
    } else if (level == LOGERROR && logLevel <= LOGERROR) {
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
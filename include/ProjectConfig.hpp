#ifndef PROJECTCONFIG_HPP
#define PROJECTCONFIG_HPP

/**
 * @brief 日志级别
 *
 * - LOGTEST: 测试
 *
 * - LOGINFO: 信息
 *
 * - LOGERROR: 错误
 *
 * - NOLOG: 无日志
 */
enum class LogLevel {
    LOGTEST,
    LOGINFO,
    LOGERROR,
    NOLOG,
};
using enum LogLevel;

static const LogLevel DEBUG_LOG = LOGTEST;

#endif // PROJECTCONFIG_HPP
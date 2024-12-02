#include "Utilities.h"

/**
 * @brief Formats a string using a printf-like format string and variadic arguments.
 *
 * This function takes a format string and a variable number of arguments,
 * formats the string according to the format specifiers, and returns the
 * resulting string.
 *
 * @param fmt The format string containing format specifiers.
 * @param ... The variadic arguments to be formatted according to the format specifiers.
 * @return A formatted string.
 * @throws std::invalid_argument If the format string is invalid.
 */
string format(const string &fmt, ...) {
    va_list args;
    va_start(args, fmt); // NOLINT(clang-diagnostic-varargs)
    int size = vsnprintf(nullptr, 0, fmt.c_str(), args);
    va_end(args);
    if (size < 0) {
        throw invalid_argument("Invalid format string");
    }
    vector<char> buffer(size + 1);
    va_start(args, fmt); // NOLINT(clang-diagnostic-varargs)
    vsnprintf(buffer.data(), buffer.size(), fmt.c_str(), args);
    va_end(args);
    return string(buffer.data());
}
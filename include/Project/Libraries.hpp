#ifndef PROJECTSTANDARDLIBS_HPP
#define PROJECTSTANDARDLIBS_HPP

#include <coroutine>
#include <cstdarg>
#include <format>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <argparse/argparse.hpp>
#include <crow.h>
#include <nlohmann/json.hpp>

using std::exception;
using std::format;
using std::function;
using std::invalid_argument;
using std::make_shared;
using std::make_unique;
using std::map;
using std::nullopt;
using std::optional;
using std::out_of_range;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using json = nlohmann::json;

#endif // PROJECTSTANDARDLIBS_HPP
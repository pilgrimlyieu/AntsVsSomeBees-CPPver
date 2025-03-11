#ifndef PROJECTINFO_HPP
#define PROJECTINFO_HPP

#include "Libraries.hpp"

#define INFO const static

namespace AVSBInfo {
INFO string PROJECT_NAME = "Ants Vs. SomeBees";                                   //!< 名称
INFO string AUTHOR = "PilgrimLyieu";                                              //!< 作者
INFO string EMAIL = "pilgrimlyieu@outlook.com";                                   //!< 联系邮箱
INFO string DESCRIPTION = "C++ version of the CS61A prject Ants Vs. SomeBees";    //!< 描述
INFO string REPOSITORY = "https://github.com/pilgrimlyieu/AntsVsSomeBees-CPPver"; //!< 仓库
INFO string LICENSE = "MIT License";                                              //!< 许可证
} // namespace AVSBInfo

#undef INFO

#endif // PROJECTINFO_HPP

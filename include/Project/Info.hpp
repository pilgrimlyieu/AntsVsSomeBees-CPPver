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

INFO unsigned VERSION_PRIMARY = 0;         //!< 主序号
INFO unsigned VERSION_PHASE = 1;           //!< 阶段号
INFO unsigned VERSION_BUILD = 0;           //!< 构建号
INFO unsigned VERSION_PATCH = 2;           //!< 补丁号
INFO string VERSION_CODENAME = "SeaOtter"; //!< 代号

INFO string VERSION = format("{0}.{1}.{2}-{3}", VERSION_PRIMARY, VERSION_PHASE, VERSION_BUILD,
                             VERSION_CODENAME); //!< 版本号
INFO string FULL_VERSION = format("{0}.{1}.{2}-{3}-patch.{4}", VERSION_PRIMARY, VERSION_PHASE,
                                  VERSION_BUILD, VERSION_CODENAME, VERSION_PATCH); //!< 完整版本号

} // namespace AVSBInfo

#undef INFO

#endif // PROJECTINFO_HPP
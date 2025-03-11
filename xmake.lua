-- 调整设置
local enable_test = false
local manually_manage_crow = true

-- 规则
add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })
add_rules("mode.debug", "mode.release")

-- 目标名称
local target_name = "Avsb"

-- 版本信息
local version_primary = 0
local version_phase = 1
local version_build = 0
local version_patch = 3
local version_codename = "SeaOtter"
local version = string.format("%d.%d.%d-%s", version_primary, version_phase, version_build, version_codename)
local full_version = string.format("%s-patch.%d", version, version_patch)
set_configvar("VERSION", version)
set_configvar("FULL_VERSION", full_version)
add_configfiles("src/ProjectVersion.cpp.in")
add_files("$(buildir)/ProjectVersion.cpp")

-- 设置编译工具链
set_languages("cxx20")
set_targetdir("build")
set_toolchains("clang")
set_defaultmode("debug")
set_defaultarchs("x86_64")

-- 常量
local lib_name = string.format("%sLib", target_name)
local platform = os.host()
local arch = os.arch()

-- 平台相关设置
if platform == "windows" then
    set_defaultplat("mingw")
elseif platform == "linux" then
    set_defaultplat("linux")
end

-- 依赖
add_requires("argparse")
add_packages("argparse")
add_requires("nlohmann_json")
add_packages("nlohmann_json")
if is_plat("mingw") and manually_manage_crow then
    add_includedirs( 
        "dependencies",
        "dependencies/asio",
        "dependencies/crow"
    )
else
    -- Windows OpenSSL 一直失败 :(
    add_requires("crow")
    add_packages("crow")
end
if enable_test then
    add_requires("catch2")
end

-- 编译选项
if is_plat("mingw") then
    add_syslinks("wsock32", "ws2_32") -- Windows 需要链接以支持网络功能
    add_cxxflags("-stdlib=libc++")
    if is_mode("release") then
        add_cxxflags("-static")
        add_ldflags("-static")
    end
end

-- 编译文件
add_includedirs(
    "include",
    "include/Ants",
    "include/Bees",
    "include/Exceptions",
    "include/GUI",
    "include/Places",
    "include/Plans",
    "include/Project"
)
add_files("src/**.cpp")
if is_plat("mingw") and is_mode("release") then
    add_files("src/resource.rc")
end

-- 编译模式相关设置补充
if is_mode("debug") then
    add_defines("DEBUG")
    target_name = string.format("%sDebug", target_name)
    lib_name = string.format("%sDebug", lib_name)
elseif is_mode("release") then 
    add_defines("RELEASE")
elseif is_mode("check") then
    set_policy("build.sanitizer.address", true)
    set_symbols("debug")
    set_optimize("none")
    target_name = string.format("%sCheck", target_name)
    lib_name = string.format("%sCheck", lib_name)
    add_cxxflags(
        "-fno-strict-aliasing",
        "-fno-omit-frame-pointer",
        "-ftrapv",
        "-fstack-protector-all",
        "-fstack-check",
        "-fstack-clash-protection",
        "-Wall"
    )
end

-- 静态库
target(lib_name)
    set_kind("static")

-- 二进制文件
target(target_name)
    set_default(true)
    set_kind("binary")
    add_deps(lib_name)

-- 构建后操作
after_build(function (target)
    -- 复制静态资源文件到构建目录
    os.mkdir("$(buildir)/static")
    os.mkdir("$(buildir)/templates")
    os.cp("static", "$(buildir)")
    os.cp("templates", "$(buildir)")
    print("Resource files copied to build directory")
    -- 打包
    if not is_mode("release") then
        return
    end
    import("core.project.config")
    local target_file = target:targetfile()
    local zip_name = string.format("%s-v%s-%s-%s.zip", target_name, version, platform, arch)
    local zip_path = string.format("%s/%s", config.buildir(), zip_name)
    if platform == "windows" then
        local powershell_command = string.format(
            "Compress-Archive -Force -Path '%s', 'static', 'templates' -DestinationPath '%s'",
            target_file,
            zip_path
        )
        os.execv("powershell", { "-NoProfile", "-Command", powershell_command })
    else
        os.cd("$(buildir)")
        local target_basename = path.filename(target_file)
        os.execv("zip", {
            "-qFSr",
            zip_name,
            target_basename,
            "static",
            "templates"
        })
        os.cd("..")
    end
    print("Package created: " .. zip_path)
end)

-- -- 测试目标
-- for _, file in ipairs(os.files("test/**/test_*.cpp")) do
--     local group = path.directory(path.relative(file, "./test"))
--     local name = path.basename(file)
--     target("test/" .. group .. "/" .. name)
--         set_default(false)
--         set_kind("binary")
--         set_group(group)

--         remove_files("src/Main.cpp")
--         add_tests(name)
--         add_files(file)
--         add_deps(lib_name)
--         if enable_test then
--             add_packages("catch2")
--         end
-- end

add_rules("mode.debug", "mode.release")

add_requires("argparse")
add_requires("catch2")
-- add_requires("crow") -- OpenSSL 一直失败 :(
add_requires("nlohmann_json")

set_languages("cxx20")
set_targetdir("build")
set_toolchains("clang")
set_defaultmode("debug")
set_defaultplat("mingw")

add_includedirs(
    "dependencies",
    "dependencies/asio",
    "dependencies/crow",

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

add_packages("nlohmann_json")
add_packages("argparse")

add_syslinks("wsock32", "ws2_32")

local target_name = "Avsb"
local lib_name = target_name .. "Lib"

if is_mode("debug") then
    add_defines("DEBUG")
    target_name = target_name .. "Debug"
    lib_name = lib_name .. "Debug"
elseif is_mode("release") then 
    add_defines("RELEASE")
elseif is_mode("check") then
    -- set_policy("build.sanitizer.address", true)
    set_symbols("debug")
    set_optimize("none")
    target_name = target_name .. "Debug"
    lib_name = lib_name .. "Debug"

    add_cxflags(
        "-fno-strict-aliasing",
        "-fno-omit-frame-pointer",
        "-ftrapv",
        "-fstack-protector-all",
        "-fstack-check",
        "-fstack-clash-protection",
        "-Wall"
    )
end

target(lib_name)
    set_kind("static")

target(target_name)
    set_default(true)
    set_kind("binary")

    add_files("src/Main.cpp")
    add_deps(lib_name)

after_build(function (target)
    os.mkdir("$(buildir)/static")
    os.mkdir("$(buildir)/templates")
    os.cp("static", "$(buildir)")
    os.cp("templates", "$(buildir)")
    print("Resource files copied to build directory")
end)

for _, file in ipairs(os.files("test/**/test_*.cpp")) do
    local group = path.directory(path.relative(file, "./test"))
    local name = path.basename(file)
    target("test/" .. group .. "/" .. name)
        set_default(false)
        set_kind("binary")
        set_group(group)

        remove_files("src/Main.cpp")
        add_tests(name)
        add_files(file)
        add_deps(lib_name)
        add_packages("catch2")
end

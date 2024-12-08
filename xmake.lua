add_rules("mode.debug", "mode.release")

add_requires("catch2")

set_languages("cxx20")
set_targetdir("build")
set_toolchains("clang")
set_defaultmode("debug")
set_defaultplat("mingw")

add_includedirs(
    "include",
    "include/Ants",
    "include/Bees",
    "include/Exceptions",
    "include/Places",
    "include/Plans"
)
add_files("src/**.cpp")

target("MyToyLib")
    set_kind("static")

target("MyToy")
    set_default(true)
    set_kind("binary")

    add_files("src/Main.cpp")
    add_deps("MyToyLib")

if is_mode("debug") then
    add_defines("DEBUG")
elseif is_mode("release") then 
    add_defines("RELEASE")
elseif is_mode("check") then
    set_symbols("debug")
    set_optimize("none")

    add_cxflags(
        "-fno-strict-aliasing",
        "-fno-omit-frame-pointer",
        "-ftrapv",
        "-fstack-protector-all",
        "-fstack-check",
        "-fstack-clash-protection",
        "-Wall"
    )

    if is_os("linux") then
        -- Not supported for MinGW64 in Windows
        local sanitize = "address"
        add_cxflags(
            "-fsanitize=" .. sanitize
        )
        add_ldflags(
            "-fsanitize=" .. sanitize
        )
    end
end

for _, file in ipairs(os.files("test/**.cpp")) do
    local group = path.directory(path.relative(file, "./test"))
    local name = path.basename(file)
    target("test/" .. group .. "/" .. name)
        set_default(false)
        set_kind("binary")
        set_group(group)
        remove_files("src/Main.cpp")
        add_tests(name)
        add_files(file)
        add_defines("TEST")
        add_deps("MyToyLib")
        add_packages("catch2")
end

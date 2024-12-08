add_rules("mode.debug", "mode.release")

set_languages("cxx20")
set_targetdir("build")
set_toolchains("clang")
set_defaultmode("debug")

add_requires("catch2")

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
    set_kind("binary")
    set_default(true)
    add_files("src/Main.cpp")

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
        sanitize = "address"
        add_cxflags(
            "-fsanitize=" .. sanitize
        )
        add_ldflags(
            "-fsanitize=" .. sanitize
        )
    end
end


for _, file in ipairs(os.files("test/**.cpp")) do
    local name = path.directory(path.relative(file, "./test")) .. "_" .. path.basename(file)
    local test_name = "test_" .. name
    target(test_name)
        set_kind("binary")
        remove_files("src/Main.cpp")
        add_tests(name)
        add_files(file)
        add_deps("MyToyLib")
        add_packages("catch2")
end

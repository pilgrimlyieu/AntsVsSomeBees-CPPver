add_rules("mode.debug", "mode.release")

set_languages("cxx17")
set_targetdir("build")
set_toolchains("clang")

target("MyToy")
    set_kind("binary")

    add_files(
        "src/*.cpp",
        "src/Ants/*.cpp",
        "src/Bees/*.cpp",
        "src/Places/*.cpp",
        "src/Utilities/*.cpp"
    )
    add_includedirs(
        "include",
        "include/Ants",
        "include/Bees",
        "include/Places",
        "include/Utilities"
    )

if is_mode("check") then
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
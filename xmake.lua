add_rules("mode.debug", "mode.release", "mode.check")

set_languages("c++17")
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

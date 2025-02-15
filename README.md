# Ants Vs. SomeBees (C++ version)

> 项目介绍见博文 [**Ants Vs. SomeBees (C++ 版本) 介绍**](https://pilgrimlyieu.github.io/2025/02/ants-vs-somebees)。
> 项目开发历程见博文 [**C++ 项目 Avsb 回顾与总结**](https://pilgrimlyieu.github.io/2025/02/ants-vs-somebees-development)。

> 这是一个用于验收的临时简单的 README，更多细节有待完善。
> 稍微详细一点的内容、随意的演示、评分细则，同时也是视频中用的文档（修正前），可见 [doc/demo.md](doc/demo.md)。

## 项目简介

这是一个基于 CS61A 项目作业 [**A**nts **V**s. **S**ome**B**ees](https://cs61a.org/proj/ants)、使用了 C++ 重新实现、并添加了一些新的功能的项目。

软工 I 课程就已经了解过这个项目作业的大体情况了，因此细节不在此过多展开。原版游戏的全部功能基本上都实现了。

另外其实 Avsb 有多个版本，例如说[我完成的版本](https://github.com/pilgrimlyieu/SEC-Homework/tree/main/Python/proj3/240-2024spring_softwareengineering_python_proj3)就和上面的链接给出的不一样。起初我是基于我自己完成的版本来写的，因此上面链接中没有提及的各种 Bee 基本都有得到实现[^except]。不过在完成游戏逻辑的实现，即将着手 Web GUI 的实现时，因为上面的新版使用了 Flask，前端更为简洁，因此也将部分游戏逻辑进行了修改，以适应新版的 Python 原代码。

[^except]: 除了 Hornet，因为这个没有资源，而且会引入菱形继承。

命令行参数如下：

```
$ ./Avsb --help
Usage: Ants vs. SomeBees [--help] [--version] [[--difficulty DIFFICULTY]|[--plan PLAN]] [--water] [--open] [--food FOOD] [--log LEVEL] [--port PORT] [--config CONFIG] [--save]

Optional arguments:
  -h, --help                   shows help message and exits
  -v, --version                prints version information and exits
  -d, --difficulty DIFFICULTY  sets difficulty of game (test/easy/normal/hard/extra-hard) [default: "normal"]
  -a, --plan PLAN              path to custom assault plan JSON file
  -w, --water                  loads a full layout with water
  -o, --open                   automatically open the game in a browser (maybe not work in your OS!)
  -f, --food FOOD              number of food to start with when testing [default: 2]
  -l, --log LEVEL              sets log level (0:TEST, 1:INFO, 2:ERROR, 3:NONE) [default: 1]
  -p, --port PORT              sets the port for the server [default: 18080]
  -c, --config CONFIG          path to config file [default: "./config.json"]
  -s, --save                   save game configuration to file and exit
```

## 编译运行

本项目原则上是跨平台的，我成功在 Windows 和 Linux[^linux] 上编译并运行。由于我没有 macOS 设备，并未为其添加支持，不过理论上是可以通过修改构建脚本来支持的。

[^linux]: WSL2 Ubuntu x86_64

本项目采用 [XMake](https://xmake.io) 作为构建工具，构建脚本位于项目根目录下的 `xmake.lua` 文件中。

同时本项目采用的是 **clang** 工具链而非 gcc 工具链，在 Windows 下用的是 [MSYS2](https://www.msys2.org) 的 clang，Linux 下用的是安装包管理器安装的 clang，版本分别为：

```shell
$ clang --version
clang version 19.1.6
Target: x86_64-w64-windows-gnu
Thread model: posix
InstalledDir: D:/Software/msys64/clang64/bin
```

```shell
$ clang --version
Ubuntu clang version 18.1.3 (1ubuntu1)
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

经过实测，附带 LLVM 的 WinLibs 的 MinGW64 无法完成编译。工具链的安装与配置不在此展开，下面假定已经正确完成了工具链的安装与配置。

在讲述步骤之前还需要提及一些需要注意的部分：

没想到吧，其实项目还提供了测试支持，只是我没时间写了。使用的是 catch2 包。我这里安装 catch2 包需要一些鬼畜的操作。如果需要启用测试，可以将 `xmake.lua` 开头部分的 `enable_test` 改为 `true`。同时相关测试的构建目标也已经在构建脚本中定义好了。

此外在 Windows 中，我始终无法安装 crow 包，因此我将 crow 包（以及 asio 包）直接放在了 `dependencies` 目录下，而非通过 XMake 进行管理。`dependencies` 目录以加入 `.gitignore`，因此如果在 Windows 下编译，要么修改编译脚本，使用 XMake 进行包管理并成功，要么就是自己去找 [crow](https://github.com/CrowCpp/Crow) 和 [asio](https://github.com/chriskohlhoff/asio) 包，并按照构建脚本中的路径放置。

好消息是，Linux 中上面的问题都不存在。

两个平台的构建命令均为

```shell
$ xmake f -m release && xmake build
```

含义为，设置构建模式为 release，然后构建项目。

构建完成后，可执行文件位于 `build` 目录下，名称为 `Avsb.exe`（Windows）或 `Avsb`（Linux），与静态资源与模板文件一起，位置正确运行即可。

由于游戏本体文件与资源文件分开的，因此还需要打包成压缩包比较合适。这个在 Windows 的 VS Code 下有相关任务配置，需要安装 [PowerShell](https://github.com/PowerShell/PowerShell)[^pwsh] 和 XMake，然后执行 Pack Release 任务即可。

[^pwsh]: 不是 5 这个老古董，是 7 的新版。

此外还有代码文档的构建，除了 Windows 的 VS Code 有 Generate Document 等相关任务外，还可以手动通过命令行进行构建。前置要求是安装了 [Doxygen](https://www.doxygen.nl)，同时还要有 [Graphviz](https://graphviz.org) 的支持（也可以修改 `Doxyfile` 以禁用 Dot）。构建命令为

```shell
$ xmake doxygen -o doc
```

构建完成后，HTML 文档位于 `doc/html` 目录下，可以通过打开 `doc/html/index.html` 查看。

## 项目结构

项目的结构如下：

```
 Avsb
├──  .vscode
├──  .xmake
├──  build
├──  dependencies
├──  doc
├──  include
├──  material
├──  src
├──  static
├──  templates
├──  test
├──  .clang-format
├──  .clang-tidy
├──  .clangd
├──  .gitignore
├──  Doxyfile
├── 󰂺 README.md
└──  xmake.lua
```

- `.vscode`：VS Code 配置文件夹
- `.xmake`：XMake 缓存文件夹
- `build`：构建输出文件夹
- `dependencies`：依赖包文件夹
- `doc`：文档文件夹
- `include`：头文件文件夹
- `material`：游戏参考资料文件夹（指要求的 PDF）
- `src`：源代码文件夹
- `static`：静态资源文件夹
- `templates`：模板文件夹
- `test`：测试文件夹
- `.clang-format`：Clang 格式化配置文件
- `.clang-tidy`：Clang 静态分析配置文件
- `.clangd`：Clangd 配置文件
- `.gitignore`：Git 忽略文件
- `Doxyfile`：Doxygen 配置文件
- `README.md`：项目说明文件
- `xmake.lua`：XMake 构建脚本

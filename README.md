# <center>Parser</center>

# 项目背景

`Boost::Spirit` 库的初次实践，搭建C++的词法分析器。

涉及到的库：~~`boost::spirit::classic`~~、`boost::spirit::qi`、`boost::spirit::karma`、`boost::spirit::lex`、*`boost::spirit::phoenix`*。

# 安装

## Boost库的安装教程：

> 获得Boost副本的最可靠方法是从[SourceForge](https://www.boost.org/users/history/version_1_73_0.html)下载发行版：

* Linux:

    > 下载[boost_1_73_0 .tar.bz2](https://www.boost.org/users/history/version_1_73_0.html)。
    >
    > 在要放置Boost安装的目录中，执行
    >
    > `` $ tar --bzip2 -xf / path / to / boost_1_73_0 .tar.bz2 ``

* Windows:

    > 参考Boost官方教程:[Windows入门](https://www.boost.org/doc/libs/1_74_0/more/getting_started/windows.html)

# 使用

## 编译

* 编译样例代码
  * **Linux**

    假设*Boost_1_74_0*库在用户家目录下：

    `` g++ test.cpp -o test -I ~/boost_1_74_0``

  * Windows

    略

* 运行

    直接运行即可，无其他附加项

# 主要负责人

[@zhongqi(2858199552)](https://github.com/2858199552)

# 参与贡献方式

1. ``fork``该库
2. ``clone``至本地
3. 查看 ***dev*** 分支的开发进度、当前任务。选择适合你的**新特性开发**、**BUG修复**、**完善文档**等工作
4. ``pull request`` 等待 *review*

# 开源协议

[MIT LICENSE](https://github.com/2858199552/parser/blob/main/LICENSE)

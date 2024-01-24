# ShotX


<div align=center>
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2020/logo.svg" height="240" width="240" />
</div>

<br>

## 项目介绍

<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>

![](https://img.shields.io/badge/language-c++-orange.svg) ![](https://img.shields.io/badge/language-Qt-orange.svg) ![](https://img.shields.io/github/license/xmuli/ShotX) ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/xmuli/ShotX)

[![macos-badge](https://github.com/xmuli/ShotX/workflows/MacOS/badge.svg)](https://github.com/xmuli/ShotX/workflows/MacOS/badge.svg)  [![win-badge](https://github.com/xmuli/ShotX/workflows/Windows/badge.svg)](https://github.com/xmuli/ShotX/workflows/Windows/badge.svg)  [![ubuntu-badge](https://github.com/xmuli/ShotX/workflows/Ubuntu/badge.svg)](https://github.com/xmuli/ShotX/workflows/Ubuntu/badge.svg)   ![GitHub stars](https://img.shields.io/github/stars/xmuli/ShotX?style=social) ![GitHub forks](https://img.shields.io/github/forks/xmuli/ShotX?style=social) 

<br>

> 一款轻的、迅速的截图软件 `ShotX`



起源最初的梦，写一个随心所欲的截图软件，至今(2024.01.24)也写了三个不同程度的，由易到难，供大家参考；

更详细的开发细节文档，有空再给写，补充在系列中，QQ 交流群: [418103279](https://qm.qq.com/cgi-bin/qm/qr?k=jsD03QzMohGZm0TqYAFh3BvKOpCGlTcT&jump_from=webapi&authKey=DMUwiCQ6ta95PoH8JmtZ+Jz9y7Ozg3yinEsxmm92rNXZRVeMPD7NRgjU+dmUI8Xu) 



|                  项目                   |                             详细                             |                             介绍                             |                 镜像(Gitee)                 |
| :-------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :-----------------------------------------: |
| [ShotX](https://github.com/XMuli/ShotX) |            新手级的截图，适合初学 Qt/C++ 不到一年            |           一款极简的截图工具(支持 Win，Mac，Linux)           |    [url](https://gitee.com/XMuli/ShotX)     |
|    [Flipped](https://c.xmuli.tech/)     |       中级难度的截图，适合已学习 Qt/C++ 一两年经验进阶       | 简洁且漂亮的截图的软件工具，支持 Windows，MacOS，Linux 平台  | [url](https://gitee.com/XMuli/FlippedPages) |
|   [Sunny](https://sunny.xmuli.tech/)    | 高级难度的截图，适合已深入研究 Qt/C++ 三五年经验，属于商业级的成熟作品，**是截图系列的最高水准之作** | Simple and beautiful screenshot software tool for Windows, MacOS and Linux；已上架 Deepin/UOS Store，Spark Store 等 |  [url](https://gitee.com/XMuli/SunnyPages)  |

<br>

## Compilation

### Dependencies

- Qt >= 5.15.2
- CMake >= 3.16
- MSVC >= 2022 | MinGW >=  8.1.0 | GCC >= 9.4 | Clang >= 12.0

​	NOTE: This is a successfully compiled dependency version, lower versions have not been tested.

<br>

### Build

- **Kit Tools:** Windows 10 & Qt 5.15.2 & CMake 3.24.1 & MSVC 2022 ( or MinGW 8.1.0)

- **Compile Step:**

  ```bash
  qmake
  make -j16
  ```

<br>

## 运行效果

**MacOS**

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401250051823.jpg" width="100%"/>

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401250051067.png" width="400"/> 

**Windows**

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401250055738.png" width="100%"/>



## 教程

**ShotX**

- [GitHub Code](https://github.com/XMuli/shotx) 

**FLIPPED** 

- 开发教程: [基于 QT 开发 FLIPPED ：简易且漂亮的跨平台截图贴图软件](https://blog.csdn.net/qq_33154343/article/details/130053230)

- 视频演示效果： [bilibili](https://www.bilibili.com/video/BV1rX4y1D7EZ/)

**Sunny**

- [系类开发教程](https://github.com/XMuli/QtExamples)
- 视频演示效果: 待续



## 贡献

如果对您有帮助，或者觉得有用，**您可以点击该仓库的⭐ Star 🍴 Fork 两个图标，方便抬手之间，说点赞的手，** 手留余香；其次可以请我喝一杯冰的快乐水。 

<details>
    <summary> <b>"当然，你也可以送我一听冰凉的可乐 [捐赠/打赏 ← 点击展开二维码]"</b></summary>
  <p> 如果对您有帮助，或者觉得有用，您可以点击该仓库的⭐ Star 🍴 Fork 两个图标，方便抬手之间，说点赞的手， 手留余香；其次可以我喝一杯冰的快乐水 - </p>
  <pre><img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202302282339037.png" width="80%"/></pre>
</details>



## 作者

|    Title    |                            Detail                            |
| :---------: | :----------------------------------------------------------: |
| WeChat / QQ | [252311126](https://wpa.qq.com/authd?IDKEY=31f3ef7312b39e2c8dc822ae2f4c3b3118e1a6f31cc83373) |
|   GitHub    |               [偕臧](https://github.com/XMuli)               |



## 系列教程

[QtExamples](https://github.com/XMuli/QtExamples)  "欢迎 `star` ⭐ 和 `fork` 🍴 这个系列的 `C++ / QT / DTK` 学习，这里你可以学到如何亲自编写这类软件的经验，这是一系列完整的教程，并且**免费**！"

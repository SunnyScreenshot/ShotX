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

更详细的开发细节文档，有空再给写，补充在系列中，QQ 交流群: [![alt text](https://img.shields.io/badge/QQ_Groups-418103279-brightgreen)](https://qm.qq.com/q/X6tar2pWWk)

<br>

## 截图作品系列

很久之前就想些一个软件截图的软件，目前一共写如下三个层级的难度作品，提供大家参考

- **Ⅰ. 新手之作 ShotX**
  - 项目地址：[ShotX](https://github.com/XMuli/ShotX)   \|   [镜像](https://gitee.com/XMuli/ShotX)
  - 功       能：①基本的截图功能，复制和保存，②右键托盘及菜单，③支持 Window，MacOS，Linux，④攥写 Github-Action 的 CI/CD 自动脚本 .yml；实现自动打包和发布，⑤更多见 README 和 源码
  - 描        述：新手级的截图，适合初学 Qt/C++ 入门者
- **Ⅱ. 高级之作 FLIPPED**
  - 官       网：[flipped.xmuli.tech](https://flipped.xmuli.tech/)
  - 项目地址：[FLIPPED](https://github.com/XMuli/FlippedPages)  \|  [镜像](https://gitee.com/XMuli/FlippedPages)
  - 功       能：①贴图和钉图，②多屏截图，延时截图，自定义截图，③智能检测窗口矩形（Windows & Linux），④矩形、椭圆、箭头、画笔、马赛克、文本、序号，⑤撤销、重做（多级）、保存、取消、拷贝到剪切板，⑥截图框样式三套，且主题色提供自定义；屏幕十字线样式自定义，⑦国际化：英文、简体中文、繁体中文；字体和字号自定义，⑧支持设置窗口，托盘，截图区域之间的流畅切换，⑨更多见 README 和 源码
  - 描        述：高级难度，适合已学习 Qt/C++ 数年经验进阶，需同类型软件的代码借鉴，但可探索中独立写一个大的软件。出发于隐私安全，无任何联网功能。
- **Ⅲ. 商业级别的成熟之作 Sunny (推荐)**
  - 官       网：[sunny.xmuli.tech](https://sunny.xmuli.tech/)
  - 项目地址：[Sunny](https://github.com/XMuli/sunnypages)  \|  [镜像](https://gitee.com/XMuli/SunnyPages)
  - 功       能：是 FLIPPED 作品的超集合，常见截图功能都都包含。还包含额外的功能：① "图片翻译" (中/英/日/韩/俄等)，和"OCR 提取文字"，也支持用户私人token 的额度使用 ，② .iss 脚本和 CMake 来提供便携版，安装版，③ 绘画工具栏的亚克力效果，且支持跨平台（毛玻璃效果），④编辑文本支持富文本，同一个注释可采用多个字体和颜色等（暂未遇到其它同类软件也能做到），⑤全新的 UI/UE 设计交互，“设置窗口” 无任何缝隙拼接感，颜值达到简约美观，⑥优化截屏完成后的内存释放；⑦国际化翻译更方便，⑧CMake 重写拆分为 EXE + DLL 隔离，⑨进行代码签名，方便下载校验和防篡改，⑩成功上架 Window 的微软商店，Linux 的 深度/统信商店，以及三方的星火商店等；麒麟商店也在上架待审核
  - 描        述：基于前两个的项目经验和不足，直接重写了一套新的框架和UI界面；目前个人从代码功能和产品体验来说，已经达到 工程代码整洁、规范、稳定和健壮性，优秀的解耦机制，漂亮简约得 UI / UX 设计，可以随时应对变化的实际需求，很久之内都无需重构了。定位为 漂亮和简洁，功能实用为主。

|  项目   |                             描述                             |                           开发经验                           |
| :-----: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|  ShotX  |                      功能极简的截图工具                      |           简易，新手级的截图，适合初学 Qt/C++ 入门           |
| FLIPPED |   简洁且漂亮，功能完整的截图软件；隐私安全，无任何联网功能   | 高级难度，属 Qt/C++ 数年经验的进阶作品，在借鉴同类作品的代码时，可于探索中独立完成的一个大的软件 |
|  Sunny  | 一款简洁且漂亮的截图的软件工具。亦支持图片翻译和OCR；已上架微软商店，深度/统信商店，及三方的星火商店等 | 专业级作品，适合已多年沉浸研究 Qt/C++ 经验，随心所欲写任意所需功能，**属于商业级的成熟作品，是本截图系列的最高水准之作** |



> **注：** ShotX，FLIPPED，Sunny 这三款均支持跨平台 Windows / MacOS / Linux。
>
> **笔记：** Sunny  =  FLIPPED的功能重构 + 代码重构 + UI重构 + 网络功能（图片翻译+OCR）+ 上架应用商店 + 后续新功能；而 ShotX 是最早的练手探索

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



## 贡献

如果对您有帮助，或者觉得有用，**您可以点击该仓库的⭐ Star 🍴 Fork 两个图标，方便抬手之间，说点赞的手，** 手留余香；其次可以请我喝一杯冰的快乐水。 

<details>
    <summary> <b>"当然，你也可以送我一听冰凉的可乐 [捐赠/打赏 ← 点击展开二维码]"</b></summary>
  <p> 如果对您有帮助，或者觉得有用，您可以点击该仓库的⭐ Star 🍴 Fork 两个图标，方便抬手之间，说点赞的手， 手留余香；其次可以我喝一杯冰的快乐水 - </p>
  <pre><img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202302282339037.png" width="80%"/></pre>
</details>


## 作者

GitHub: [偕臧](https://github.com/XMuli)



## 系列教程

[QtExamples](https://github.com/XMuli/QtExamples)  "欢迎 `star` ⭐ 和 `fork` 🍴 这个系列的 `C++ / QT / DTK` 学习，这里你可以学到如何亲自编写这类软件的经验，这是一系列完整的教程，并且**免费**！"

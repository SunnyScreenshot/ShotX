#ifndef SCREENSHOTS_H
#define SCREENSHOTS_H

#include "systeminfo.h"
#include <QPoint>
#include <QWidget>

static const int g_width = 4;                           // 灵敏度调节 [且便于测试]

enum ScreenType {
    Select = 0x0001,                                    // 选择截图矩形
    Move = 0x0002,                                      // 移动矩形区域
    SetSize = 0x0004                                    // 设置矩形大小
};
Q_DECLARE_FLAGS(ScreenTypes, ScreenType)                // 枚举 ScreenType 生成宏 ScreenTypes
Q_DECLARE_OPERATORS_FOR_FLAGS(ScreenTypes)              // 重载宏 ScreenTypes 的 |() 函数

enum PosType {
    Contains,                                           // 点在矩形内部
    Cross,                                              // 点在矩形线上
    External,                                           // 点在矩形外部
    Other                                               // 未知
};

enum PosArrow {                                         // 鼠标在线框时候的方向枚举
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    UnKnown
};

class ToolBoxWindow;
class ScreenShots : public QWidget
{
    Q_OBJECT
public:
    ~ScreenShots();

    static ScreenShots *instances();
    void init();
    QRect setCurrRect();                                // 判断当前矩形的大小
    PosType isInArea(QPoint pos, int width = g_width);  // 判断鼠标是否在截图矩形之中
    bool DectionAndSetMouseTracking(bool b = false);    // 检测并且开启鼠标跟踪

private:
    ScreenShots();                                      // 构造函数为私有
    QPoint offset();                                    // 偏移量（m_moveEndPos - m_moveStaPos）
    void updateCursor(QPoint pos, int width = 0);       // 依据光标和矩形所处的位置，刷新鼠标形状
    const QPixmap *pixmap();
    const QPixmap *basePixmap();                        // 背景图
    void drawScreenRect(QRect &rect, QPainter &pa);     // 绘画截图黑白线框
    void drawAnchor(QPainter &pa, bool b = true, int r = g_width); // 绘画线框的八个锚点
    PosArrow posArrow(QPoint pos, int width = g_width);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool   m_mouseTracking;                             // 鼠标跟踪是否开启标志
    bool   m_cursor;                                    // 鼠标样式是否修改标志
    QRect  m_rect;                                      // 截图矩形框大小（前台）
    QPoint m_staPos;
    QPoint m_endPos;
    QPoint m_moveStaPos;
    QPoint m_moveEndPos;
    QPoint m_sizeStaPos;
    QPoint m_sizeEndPos;
    QPoint m_translate;                                    // 快捷键移动矩形位置
    QMargins m_sizeMargins;                                // 快捷键调整矩形大小
    ScreenTypes m_screenType;

    QPixmap       *m_pixmap;                               // 原图
    QPixmap       *m_basePixmap;                           // 背景图(= 原图 + 灰色)
    QPixmap       *m_savePixmap;                           // 保存图；
    SystemInfo    *m_sysInfo;                              // 物理屏幕基础信息
    ToolBoxWindow *m_toolBox;                              // 修改截图的工具箱
};

#endif // SCREENSHOTS_H

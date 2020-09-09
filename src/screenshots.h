#ifndef SCREENSHOTS_H
#define SCREENSHOTS_H

#include <QWidget>

class QPixmap;

enum ScreenType {
    Select = 0x001,        // 选择截图矩形
    Move = 0x0002,         // 移动矩形区域
    SetSize = 0x0004       // 设置矩形大小
};
Q_DECLARE_FLAGS(ScreenTypes, ScreenType)     // 枚举 ScreenType 生成宏 ScreenTypes
Q_DECLARE_OPERATORS_FOR_FLAGS(ScreenTypes)   // 重载宏 ScreenTypes 的 |() 函数

class ScreenShots : public QWidget
{
    Q_OBJECT
public:


    ScreenShots(QSize size);

    void init();




private:
    QRect  m_rect;
    QPoint m_staPos;
    QPoint m_endPos;
    QPoint m_moveStaPos;
    QPoint m_moveEndPos;

    QPixmap *m_pixmap;         // 原图
    QPixmap *m_basePixmap;     // 背景图(= 原图 + 灰色)
    QPixmap *m_savePixmap;     // 保存图；
};

#endif // SCREENSHOTS_H

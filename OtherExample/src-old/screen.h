#ifndef SCREEN_H
#define SCREEN_H

#include <QSize>
#include <QPoint>
#include <QRect>
#include <QFlags>

//截图类： 包含一张图片所需的信息
class Screen
{
public:
    enum Status {
        select = 0x001,           // 选择截图矩形区域
        move = 0x0002,             // 截图矩形区域移动
        setWidthHeight = 0x0004    // 更改截图矩形长宽
    };

    Q_DECLARE_FLAGS(StatusFlags, Status)   // 枚举 Status 生成宏 Statuss

    Screen();
    Screen(QSize size = QSize(0, 0));

    void init();

    void setStaPos(QPoint pos);
    void setCurPos(QPoint pos);
    void setEndPos(QPoint pos);
    void setTopLeft();
    void setTopLeft(QPoint pos);
    void setBottomRight();
    void setBottomRight(QPoint pos);
    void setWidth(int width);
    void setHeight(int height);
    void setRect(QRect& rect);
    void setRect(QPoint topLeft, QSize size);
    void setStatus(Screen::StatusFlags sta);

    const QPoint getStaPos();
    const QPoint getCurPos();
    const QPoint getEndPos();
    const int    getWidth();
    const int    getHeight();
    const QRect  getRect();
    Screen::StatusFlags getStatus();

    QPoint setOffSet();
    bool isInArea(QPoint pos);

    QPoint moveStaPos;
    QPoint moveEndPos;

private:
    QPoint staPos;
    QPoint curPos;
    QPoint endPos;
    QRect  rect;    // 最终截图的矩形区域

    Screen::StatusFlags status;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Screen::StatusFlags)   // 类外写， 重载宏 Statuss 的 |() 函数

#endif // SCREEN_H

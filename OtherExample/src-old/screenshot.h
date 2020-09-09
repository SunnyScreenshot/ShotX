#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include "screen.h"

class ScreenShot : public QWidget
{
    Q_OBJECT
public:
    ScreenShot();
    ~ScreenShot();

    void init();

//    void creatScreen();
//    void workScreen();
//    void saveScreen();

//    const QRect &screenRect();          // 获取屏幕大小， 注意多屏情况
    const QPixmap *globalScreen();       // 获取屏幕原图
    const QPixmap *backgroundScreen();   // 依据原图制作初始化的背景图

protected:
    void paintEvent(QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

private:
    QRect setCurrRect();           //当前实时的截图区域
    void drawLineRect(QRect &rect, QPainter &pa);    //绘画截图黑白线框


private:
    QPixmap *pix;        // 原图
    QPixmap *backPix;    // 背景图
    Screen  *screen;     // 截图状态
    int     dpi;         // 缩放比
};

#endif // SCREENSHOT_H

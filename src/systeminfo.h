#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QDesktopWidget>

class QScreen;
class QDesktopWidget;

class SystemInfo
{
public:
    SystemInfo();

    int   logicalDPI();
    int   physicalDPI();
    int   devicePixelRatio();
    QRect screenGeometry();                      // 获取设备屏幕大小
    QRect availableGeometry();                   // 获取可用桌面大小
    void virtualGeometry(QRect &rect, bool &b);
    void globalScreen(QPixmap *pix, QRect &rect, int num);


private:
    QScreen *m_screen;
    QDesktopWidget *m_deskWid;


};

#endif // SYSTEMINFO_H

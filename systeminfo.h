// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2020-2024 XMuli
// SPDX-GitHub: https://github.com/XMuli/shotx
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

class QDesktopWidget;
class QRect;
class QScreen;
class QPixmap;
class QDesktopWidget;

#include <QList>

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
    QPixmap *globalScreen(int &num);

private:
    QScreen *m_screen;
    QDesktopWidget *m_deskWid;
    QList<QScreen *> m_listScreen;

};

#endif // SYSTEMINFO_H

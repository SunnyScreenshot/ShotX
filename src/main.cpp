#include "mainwindow.h"
#include "screenshots.h"
#include "trayiconwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFrame>
#include <QGuiApplication>
#include "toolboxwindow.h"


int main(int argc, char *argv[])
{

//#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
//    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

//    TrayIconWindow *trayIcon = new TrayIconWindow();
//    trayIcon->show();

//    ScreenShots shot;
//    shot.show();

//    QRect rect(5, 5, 10 , 5);
//    qDebug()<<"---1--"<<rect;
//    rect.setBottomRight(rect.bottomRight() + QPoint(1, 1) + QPoint(4, 3));
//    qDebug()<<"---2--"<<rect;
//    rect.setWidth(10);
//    rect.setHeight(5);
//    qDebug()<<"---3---"<<rect;


    ToolBoxWindow toolBox;
    toolBox.show();

    return a.exec();
}

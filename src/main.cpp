#include "mainwindow.h"
#include "screenshots.h"
#include "trayiconwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFrame>
#include <QGuiApplication>
#include <QRect>
#include "toolboxwindow.h"
#include <QToolButton>
#include <QStyleFactory>


int main(int argc, char *argv[])
{

//#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
//    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

    QStringList listStyle = QStyleFactory::keys();
    foreach(QString val, listStyle)
      qDebug()<<val<<"  ";
    QApplication::setStyle("Fusion");

    TrayIconWindow *trayIcon = new TrayIconWindow();

//    trayIcon->show();

    //ToDo: 2020-09-21 有一个 bug，刚开始初始化的时候，单击托盘的时候，其“焦点”还是在托盘上(s)，
    //                 而没有转移到截图窗口上，所以得手动点击一下，才可以进行开始截图。而双击则不会有此问题（Mac 上）

    return a.exec();
}

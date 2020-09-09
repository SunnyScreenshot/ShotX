#include "mainwind.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QScreen>
#include "screenshot.h"
#include <QDateTime>

#define CURR_TIMEE QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz")

int main(int argc, char *argv[])
{

#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "2");

    QApplication a(argc, argv);

    ScreenShot shot;
    shot.setWindowIcon(QIcon(":/icons/app-icon.svg"));
    shot.show();

//    QWidget w;
//    QPushButton b("button",&w);   //生成 QPushButton对象， 其父组件为 QWidget

//    /*设置窗口大小位置*/
//    w.resize(200,300);
//    w.move(300,300);

//    /*设置按钮大小位置*/
//    b.resize(100,50);
//    b.move(50,100);
//    w.show();

//    qDebug()<<"QWidget:";
//    qDebug()<<"x()="<<w.x();
//    qDebug()<<"y()="<<w.y();
//    qDebug()<<"width()="<<w.width();
//    qDebug()<<"height()="<<w.height();
//    qDebug()<<"QWidget::geometry()";
//    qDebug()<<"x="<<w.geometry().x();
//    qDebug()<<"y="<<w.geometry().y();
//    qDebug()<<"w="<<w.geometry().width();
//    qDebug()<<"h="<<w.geometry().height();
//    qDebug()<<"QWidget::frameGeometry()";
//    qDebug()<<"x="<<w.frameGeometry().x();
//    qDebug()<<"y="<<w.frameGeometry().y();
//    qDebug()<<"w="<<w.frameGeometry().width();
//    qDebug()<<"h="<<w.frameGeometry().height();
    return a.exec();
}

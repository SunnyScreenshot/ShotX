#include "mainwindow.h"
#include "screenshots.h"

#include <QApplication>
#include <QGuiApplication>

int main(int argc, char *argv[])
{

#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    ScreenShots shot;
    shot.show();
    return a.exec();
}

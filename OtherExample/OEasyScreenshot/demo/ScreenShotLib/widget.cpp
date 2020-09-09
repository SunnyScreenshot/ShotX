#include "widget.h"
#include <QLibrary>
#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    // dll��ʽ���أ�ֻ��Ҫdll�ļ����ɣ�����Ҫ.h��.lib�ļ�
    // ��Ҫ��dll�ŵ���ִ��Ŀ¼��
    typedef void(*ScreenShortFunc)(void);

    QLibrary lib("OEScreenshot.dll");
    if (lib.load()) {
#ifndef QT_NO_DEBUG
        qDebug() << "load ok!";
#endif

       ScreenShortFunc f = (ScreenShortFunc)lib.resolve("OEScreenshot");
       if (f) {
#ifndef QT_NO_DEBUG
           qDebug() << "load ScreenShortFunc ok!";
#endif
           f();
       }
    } else {
#ifndef QT_NO_DEBUG
        qDebug() << "load error!";
#endif
    }
}

Widget::~Widget()
{
}

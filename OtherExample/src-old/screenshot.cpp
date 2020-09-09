#include "screenshot.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QKeyEvent>
#include <QtGlobal>

#define CURR_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz")

ScreenShot::ScreenShot()
{
    init();
    globalScreen();
    backgroundScreen();
}

ScreenShot::~ScreenShot()
{
    delete backPix;
}

void ScreenShot::init()
{
    pix = backPix = nullptr;
    dpi = QApplication::primaryScreen()->devicePixelRatio();
    QRect desktopRect = QApplication::desktop()->rect();
    screen = new Screen(desktopRect.size());
    setGeometry(desktopRect);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); // 窗口置顶 + 隐藏标题栏
//    QRect panelRect = QGuiApplication::primaryScreen()->geometry();   // mac 中的单个主屏幕

    setFixedSize(desktopRect.size());   // 用 resize() 的话，发现会操蛋的蛋疼

//    resize(1200, 800);
//    qDebug()<<"---init---"<<desktopRect<<"   "<<panelRect;
}

const QPixmap *ScreenShot::globalScreen()
{
    QDesktopWidget * deskWid = QApplication::desktop();  // 获取桌面的窗体对象
    QScreen *pScreen = QApplication::primaryScreen();    // 获取屏幕原始截图
    pix = new QPixmap(pScreen->grabWindow(deskWid->winId(), 0, 0, deskWid->size().width(), deskWid->size().height()));  // 截取屏幕上窗体对象所在区域的图像
//    pix->setDevicePixelRatio(pScreen->devicePixelRatio());

//    pix->save(CURR_TIME + "pix.png");
    QRect deskRect = deskWid->availableGeometry();   //获取可用桌面大小
    QRect screenRect = deskWid->screenGeometry();    //获取设备屏幕大小

    qDebug()<<"   屏幕个数:"<<QApplication::screens().size()
            <<"   缩放值屏幕:"<<pScreen->devicePixelRatio()
            <<"   缩放值图片:"<<pix->devicePixelRatioF()
            <<"   虚拟桌面分辨率:"<<pScreen->virtualGeometry()
            <<"   虚拟桌面:"<<QApplication::desktop()->isVirtualDesktop()
            <<"   所有尺寸的屏幕集合:"<<QApplication::desktop()->rect()
            <<"   屏幕 0 分辨率:"<<QApplication::screens().at(0)->size()
//            <<"   屏幕 1 分辨率:"<<QApplication::screens().at(1)->size()
            <<"   原始截图原始大小:"<<pix->rect()
            <<"   获取返回保存大小->"<<pScreen->grabWindow(deskWid->winId(), 0, 0, deskWid->size().width(), deskWid->size().height()).rect()
            <<"   可用桌面大小"<<deskRect<<"   设备屏幕大小"<<screenRect<<endl
            <<"   逻辑DPI:"<<pScreen->logicalDotsPerInch()<<"   xDPI:"<<logicalDpiX()<<"   yDPI:"<<logicalDpiY()<<endl
            <<"   物理DPI:"<<pScreen->physicalDotsPerInch()<<"   xDPI:"<<physicalDpiX()<<"   yDPI:"<<physicalDpiY()<<endl;

    return pix;
}

const QPixmap *ScreenShot::backgroundScreen()  // 依据桌面背景全图，在其上加上蒙层，作为底层的截图
{
    if (!pix)
        return nullptr;

    QPixmap blurLayer(pix->size());  // 桌面图片上的灰色层
    blurLayer.fill(QColor(255, 255, 255, 50));
    backPix = new QPixmap(*pix);  // 没有 delete
    QPainter pa(backPix);
    pa.drawPixmap(pix->rect(), blurLayer);
//    backPix->save("backScreen.png");

    return backPix;
}

void ScreenShot::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)

    if (!pix)
        return;

    //pix->setDevicePixelRatio(2);
    QPainter pa(this);
    pa.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);   // 抗锯齿 + 平滑边缘处理
    pa.drawPixmap(this->rect(), *backPix);

    QRect selectRect = setCurrRect();  // 前台选中矩形
    QPoint offsetPos = screen->setOffSet();
    QPoint topLeft = selectRect.topLeft() + offsetPos;
    selectRect.moveTo(topLeft);
    screen->setRect(topLeft, selectRect.size());

    QRect rect(selectRect.topLeft() * dpi, selectRect.size() * dpi);  // 后台选中矩形

//    qDebug()<<"d-->"<<screen->getCurPos()<<screen->moveStaPos<<screen->moveEndPos<<screen->getRect()<<selectRect<<rect<<QString::number(screen->getStatus(), 10);

    if (screen->getWidth() > 0 && screen->getHeight() > 0) {
        pa.drawPixmap(selectRect, pix->copy(rect));
        drawLineRect(selectRect, pa);
    }

    update();
}

void ScreenShot::mousePressEvent(QMouseEvent *ev)
{
    if (screen->getStatus() & Screen::select) {
        screen->setStaPos(ev->pos());
        screen->setCurPos(ev->pos());  // 避免出现再次点击会出现弹框
        screen->setEndPos(ev->pos());
        screen->moveEndPos = screen->moveStaPos = QPoint(0, 0);
    } else if (screen->getStatus() & Screen::move){
        if (screen->isInArea(ev->pos())) {
            screen->moveStaPos = ev->pos();
            screen->moveEndPos = ev->pos();
        } else {
            screen->setStaPos(ev->pos());
            screen->setCurPos(ev->pos());  // 避免出现再次点击会出现弹框
            screen->setEndPos(ev->pos());
            screen->setStatus(Screen::select);
        }
    }

    qDebug()<<"a-->"<<screen->getStaPos()<<screen->getCurPos()<<screen->getEndPos()<<screen->getRect()<<"    --->    "<<screen->moveStaPos<<screen->moveEndPos<<QString::number(screen->getStatus(), 10);
}

void ScreenShot::mouseMoveEvent(QMouseEvent *ev)
{
    if (screen->getStatus() & Screen::select) {
        screen->setCurPos(ev->pos());
    } else if (screen->getStatus() & Screen::move) {
        screen->moveEndPos = ev->pos();

//        QPoint posSta = screen->moveStaPos - screen->getRect().topLeft();
//        QPoint posEnd = screen->moveEndPos - screen->getRect().bottomRight();
//        screen->setStaPos(ev->pos() + posSta);
//        screen->setCurPos(ev->pos() + posEnd);
    }

    screen->setOffSet();
    qDebug()<<"b-->"<<screen->getStaPos()<<screen->getCurPos()<<screen->getEndPos()<<screen->getRect()<<"    --->    "<<screen->moveStaPos<<screen->moveEndPos<<QString::number(screen->getStatus(), 10);
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *ev)
{
    if (screen->getStatus() & Screen::select) {
        screen->setEndPos(ev->pos());
        screen->setStatus(Screen::move | Screen::setWidthHeight);
    }

    if (screen->getRect().width() <= 0 | screen->getRect().height() <= 0) {
        screen->setStatus(Screen::select);
        screen->moveEndPos = screen->moveStaPos = ev->pos();
        qDebug()<<"----aa";
    } /*else {
        if (screen->getStatus() & Screen::move) {
            QPoint pos = screen->moveStaPos - screen->getRect().topLeft();
            screen->setEndPos(ev->pos() + pos);
        }

    }*/


    qDebug()<<"c-->"<<screen->getStaPos()<<screen->getCurPos()<<screen->getEndPos()<<screen->getRect()<<"    --->    "<<screen->moveStaPos<<screen->moveEndPos<<QString::number(screen->getStatus(), 10);
}


QRect ScreenShot::setCurrRect()
{
    QRect rect(0, 0, 0, 0);

    if (screen->getStaPos() == screen->getCurPos())
        return rect;

    rect.setX(qMin(screen->getStaPos().x(), screen->getCurPos().x()));
    rect.setY(qMin(screen->getStaPos().y(), screen->getCurPos().y()));
    rect.setWidth(qAbs(screen->getStaPos().x() - screen->getCurPos().x()));
    rect.setHeight(qAbs(screen->getStaPos().y() - screen->getCurPos().y()));
    return rect;
}

void ScreenShot::drawLineRect(QRect &lineRect, QPainter &pa)
{
    pa.setBrush(Qt::NoBrush);
    QPen penWhite(QColor(0, 0, 0, 1 * 255), 1);
    penWhite.setStyle(Qt::CustomDashLine);
    penWhite.setDashOffset(0);
    penWhite.setDashPattern(QVector<qreal>()<< 4 << 4);
    penWhite.setCapStyle(Qt::FlatCap);
    pa.setPen(penWhite);
//    QRect lineRect(QRect(screen->getStaPos(), screen->getCurPos()));
    pa.drawLine(QPoint(lineRect.left(), lineRect.top()), QPoint(lineRect.right(), lineRect.top()));
    pa.drawLine(QPoint(lineRect.left(), lineRect.top()), QPoint(lineRect.left(), lineRect.bottom()));
    pa.drawLine(QPoint(lineRect.left(), lineRect.bottom()), QPoint(lineRect.right(), lineRect.bottom()));
    pa.drawLine(QPoint(lineRect.right(), lineRect.top()), QPoint(lineRect.right(), lineRect.bottom()));

    QPen penBlack(penWhite);
    penBlack.setColor(QColor(255, 255, 255, 1 * 255));
    penBlack.setDashOffset(4);
    pa.setPen(penBlack);
    pa.drawLine(QPoint(lineRect.left(), lineRect.top()), QPoint(lineRect.right(), lineRect.top()));
    pa.drawLine(QPoint(lineRect.left(), lineRect.top()), QPoint(lineRect.left(), lineRect.bottom()));
    pa.drawLine(QPoint(lineRect.left(), lineRect.bottom()), QPoint(lineRect.right(), lineRect.bottom()));
    pa.drawLine(QPoint(lineRect.right(), lineRect.top()), QPoint(lineRect.right(), lineRect.bottom()));
}

void ScreenShot::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape) {
        qDebug()<<"---Esc 按键退出---";
        this->close();
    }
}






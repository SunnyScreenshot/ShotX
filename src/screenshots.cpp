#include "screenshots.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QCursor>

#define CURR_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz")

ScreenShots::ScreenShots()
{
    init();
    m_sysInfo = new SystemInfo();

    pixmap();      // 捕获原图和处理后的背景图
    basePixmap();
}

ScreenShots::~ScreenShots()
{
    delete m_pixmap;
    delete m_basePixmap;
    delete m_savePixmap;
    delete m_sysInfo;
}

void ScreenShots::init()
{
    QPoint posNull;
    m_rect = QRect();
    m_staPos = m_endPos = posNull;
    m_moveStaPos = m_moveEndPos = posNull;
    m_pixmap = m_basePixmap = m_savePixmap = nullptr;
    m_sysInfo = nullptr;
    m_screenType = ScreenType::Select;

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); // 窗口置顶 + 隐藏标题栏
    setFixedSize(QGuiApplication::screenAt(QCursor::pos())->size());   // 用 resize() 的话，发现会操蛋的蛋疼

////#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
//  QRect position = frameGeometry();
//  QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
//  position.moveCenter(screen->availableGeometry().center());
//  move(position.topLeft());
////#endif

//  qDebug()<<position<<"  "<<screen->availableGeometry();
    setWindowIcon(QIcon(":/icons/logo.svg"));
}

QRect ScreenShots::setCurrRect()
{
    if (m_staPos == m_endPos)
        return QRect();

    m_rect.setX(qMin(m_staPos.x(), m_endPos.x()));
    m_rect.setY(qMin(m_staPos.y(), m_endPos.y()));
    m_rect.setWidth(qAbs(m_staPos.x() - m_endPos.x()));
    m_rect.setHeight(qAbs(m_staPos.y() - m_endPos.y()));
    return m_rect;
}

const QPixmap *ScreenShots::pixmap()
{
    int num = -1;
    m_pixmap = m_sysInfo->globalScreen(num);
    return m_pixmap;
}

const QPixmap *ScreenShots::basePixmap()
{
    if (!m_pixmap)
        return nullptr;

    QPixmap blurPixmap(m_pixmap->size());  // 桌面图片上的灰色层
    blurPixmap.fill(QColor(255, 255, 255, 50));
    m_basePixmap = new QPixmap(*m_pixmap);  // 没有 delete
    QPainter pa(m_basePixmap);
    pa.drawPixmap(m_basePixmap->rect(), blurPixmap);
//    m_basePixmap->save("m_basePixmap.png");
    return m_basePixmap;
}

QPoint ScreenShots::offset()
{
    return (m_moveEndPos - m_moveStaPos);
}

void ScreenShots::drawScreenRect(QRect &rect, QPainter &pa)
{
    pa.save();
    pa.setBrush(Qt::NoBrush);
    QPen penWhite(QColor(0, 0, 0, 1 * 255), 1);
    penWhite.setStyle(Qt::CustomDashLine);
    penWhite.setDashOffset(0);
    penWhite.setDashPattern(QVector<qreal>()<< 4 << 4);
    penWhite.setCapStyle(Qt::FlatCap);
    pa.setPen(penWhite);
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.right(), rect.top()));
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.left(), rect.bottom()));
    pa.drawLine(QPoint(rect.left(), rect.bottom()), QPoint(rect.right(), rect.bottom()));
    pa.drawLine(QPoint(rect.right(), rect.top()), QPoint(rect.right(), rect.bottom()));

    QPen penBlack(penWhite);
    penBlack.setColor(QColor(255, 255, 255, 1 * 255));
    penBlack.setDashOffset(4);
    pa.setPen(penBlack);
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.right(), rect.top()));
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.left(), rect.bottom()));
    pa.drawLine(QPoint(rect.left(), rect.bottom()), QPoint(rect.right(), rect.bottom()));
    pa.drawLine(QPoint(rect.right(), rect.top()), QPoint(rect.right(), rect.bottom()));
    pa.restore();
}

/*!
 * \brief ScreenShots::isInArea 检测当前鼠标所处矩形的位置，返回不同的枚举状态
 * \param[in] pos 检测某点是否在矩形中的点
 * \return 矩形若不存在：为 ScreenType::Select
 *         矩形若存在：pos 在矩形内部（不含边界），返回 ScreenType::Move；
 *                   pos 在矩形边界上，返回 ScreenType::SetSize；
 *                   pos 在矩形外部（不含边界）， 返回 ~ScreenType::Select
 */
ScreenTypes ScreenShots::isInArea(QPoint pos)
{
    if (m_rect.isEmpty())
        return ScreenType::Select;

    bool b = true;
    if (m_rect.contains(pos, b)) {  // 点在矩形内部（含边界）
        if (b) {
            return ScreenType::Move;
        } else {
            return ScreenType::SetSize;
        }
    } else {  // 点在矩形外部（不含边界）
//        m_screenType = ScreenType::Select;
        return ScreenType::Select;
    }
}

void ScreenShots::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        close();
}

void ScreenShots::mousePressEvent(QMouseEvent *event)
{
    if (m_rect.isEmpty())
        m_screenType = ScreenType::Select;

    bool b = true;
    if (m_rect.contains(event->pos(), b)) {  // 点在矩形内部（含边界）   这个函数有问题
        if (b) {
            qDebug()<<"---true";
            m_screenType = ScreenType::Move;
        } else {
            qDebug()<<"---false";
            m_screenType = ScreenType::SetSize;
        }
    } else {  // 点在矩形外部（不含边界）
        m_endPos = m_staPos = event->pos();
        m_screenType = ScreenType::Select;
    }

    if (m_screenType == ScreenType::Select) {
        m_endPos = m_staPos = event->pos();
    } else if (m_screenType == ScreenType::Move) {
        m_moveEndPos = m_moveStaPos = event->pos();
    }

    qDebug()<<"---[mousePress]"<<m_rect.contains(event->pos(), true)<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
}

void ScreenShots::mouseMoveEvent(QMouseEvent *event)
{
    if (m_screenType == ScreenType::Select) {
        m_endPos = event->pos();
    } else if (m_screenType == ScreenType::Move){
        m_moveEndPos = event->pos();;
    }

    qDebug()<<"---[mouseMove]"<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
}

void ScreenShots::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_screenType == ScreenType::Select) {
        m_endPos = event->pos();
    } else if (m_screenType == ScreenType::Move){
        m_staPos = m_rect.topLeft();
        m_endPos = m_rect.bottomRight() + QPoint(1, 1);  // 这里需要探究下（怀疑刷新和线宽 1px 会这样）
        m_moveEndPos = m_moveStaPos = QPoint(0, 0);
    }

    qDebug()<<"---[mouseRelease]"<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
}

void ScreenShots::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!m_pixmap)
        return;

    QPainter pa(this);
    pa.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);   // 抗锯齿 + 平滑边缘处理
    pa.drawPixmap(QApplication::desktop()->rect(), *m_basePixmap);

    m_rect = setCurrRect();  // 前台选中矩形

    QPoint pos = offset();
    if ((!pos.isNull()) && (m_screenType & ScreenType::Move)) {
        m_rect.setTopLeft(m_rect.topLeft() + pos);
        m_rect.setBottomRight(m_rect.bottomRight() + pos);
    }

    QRect baseRect(m_rect.topLeft() * m_sysInfo->devicePixelRatio(), m_rect.size() * m_sysInfo->devicePixelRatio());  // 后台选中矩形

    qDebug()<<"---[paintEvent1]"<<m_staPos<<m_endPos<<m_rect<<"   "<<pos<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
//    qDebug()<<"---->"<< QApplication::desktop()->rect()<<m_pixmap->rect()<<m_basePixmap->rect()<<m_sysInfo->devicePixelRatio();
    if (!m_rect.isEmpty()) {
        pa.drawPixmap(m_rect, m_pixmap->copy(baseRect));
        drawScreenRect(m_rect, pa);
    }

    qDebug()<<"---[paintEvent2]"<<m_staPos<<m_endPos<<m_rect<<"   "<<pos<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);

    update();
}

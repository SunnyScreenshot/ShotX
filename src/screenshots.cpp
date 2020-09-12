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
//    setMouseTracking(true);

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
    m_mouseTracking = false;
    QPoint posNull;
    m_rect = QRect();
    m_staPos = m_endPos = posNull;
    m_moveStaPos = m_moveEndPos = posNull;
    m_trackingStaPos = m_trackingEndPos = posNull;
    m_pixmap = m_basePixmap = m_savePixmap = nullptr;
    m_sysInfo = nullptr;
    m_screenType = ScreenType::Select;

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint); // 窗口置顶 + 隐藏标题栏
//    setFixedSize(QApplication::desktop()->rect().size());
    setFixedSize(QSize(2600, 1800));
//    setFixedSize(QGuiApplication::screenAt(QCursor::pos())->size());   // 用 resize() 的话，发现会操蛋的蛋疼

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

/*!
 * \brief ScreenShots::updateCursor 依据光标和矩形所处的位置，刷新鼠标形状
 * \note \row 鼠标移动到截图矩形边框辅警，若是坐标与矩形框线相交，则图标会默认变为缩放图标，
 *            将此为这个“矩形线框的宽度” 简称为“灵敏度”；width 值越大，鼠标与线框边缘相交越容易，故称作灵敏度越高
 * \param pos 当前点
 * \param width 灵敏度调节
 */
void ScreenShots::updateCursor(QPoint pos, int width)
{
    if (m_rect.isEmpty() || width < 1)
        return;

    int x1 = m_rect.x();
    int y1 = m_rect.y();
    int x2 = m_rect.x() + m_rect.width();
    int y2 = m_rect.y() + m_rect.height();
    int w = 2 * width;

    QRect rTopLeft(x1 - width, y1 - width, w, w);
    QRect rTopRight(x2 - width, y1 - width, w, w);
    QRect rBottomLeft(x1 - width, y2 - width, w, w);
    QRect rBottomRight(x2 - width, y2 - width, w, w);
    QRect rTop(x1 + width, y1 - width, m_rect.width() - w, w);
    QRect rBottom(x1 + width, y2 - width, m_rect.width() - w, w);
    QRect rLeft(x1 - width, y1 + width, w, m_rect.height() - w);
    QRect rRight(x2 - width, y1 + width, w, m_rect.height() - w);

    if (rTopLeft.contains(pos) || rBottomRight.contains(pos))
        setCursor(Qt::SizeFDiagCursor);
    if (rBottomLeft.contains(pos) || rTopRight.contains(pos))
        setCursor(Qt::SizeBDiagCursor);
    if (rTop.contains(pos) || rBottom.contains(pos))
        setCursor(Qt::SizeVerCursor);
    if (rLeft.contains(pos) || rRight.contains(pos))
        setCursor(Qt::SizeHorCursor);
}

void ScreenShots::drawScreenRect(QRect &rect, QPainter &pa)
{
    pa.save();
    pa.setRenderHint(QPainter::Antialiasing, false);  // 若是开启防走样，反而得不到预期效果
    pa.setBrush(Qt::NoBrush);
    QPen penWhite(QColor(255, 255, 255, 1 * 255), 1);
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
    penBlack.setColor(QColor(0, 0, 0, 1 * 255));
    penBlack.setDashOffset(4);
    pa.setPen(penBlack);
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.right(), rect.top()));
    pa.drawLine(QPoint(rect.left(), rect.top()), QPoint(rect.left(), rect.bottom()));
    pa.drawLine(QPoint(rect.left(), rect.bottom()), QPoint(rect.right(), rect.bottom()));
    pa.drawLine(QPoint(rect.right(), rect.top()), QPoint(rect.right(), rect.bottom()));
    pa.restore();
}

/*!
 * \brief ScreenShots::isInArea 检测当前鼠标所处矩形的位置
 * \param[in] pos 检测某点是否在矩形中的点
 */
PosType ScreenShots::isInArea(QPoint pos, int width)
{
    if (m_rect.isEmpty())
        return PosType::Other;

    int w = 2 * width;
    QRect outboard(m_rect.x() - width, m_rect.y() - width, m_rect.width() + w, m_rect.height() + w);  // 外侧矩形
    QRect inside(m_rect.x() + width, m_rect.y() + width, m_rect.width() - w, m_rect.height() - w);   // 内侧矩形

    if (outboard.contains(pos, false)) {
        if (inside.contains(pos, true)) {  // 点在矩形内部（不含边界）
            qDebug()<<"--c--"<<pos<<"点在矩形内部";
            setCursor(Qt::SizeAllCursor);
            return PosType::Contains;
        } else {                           // 点在矩形边界上
            qDebug()<<"--c--"<<pos<<"点在矩形边界上";
            updateCursor(pos, width);
            return PosType::Cross;
        }
    } else {                                // 点在矩形外部（不含边界）
        qDebug()<<"--c--"<<pos<<"点在矩形外部（不含边界）";
        setCursor(Qt::ArrowCursor);
        return PosType::External;
    }
}

/*!
 * \brief ScreenShots::DectionAndSetMouseTracking 检测和设置鼠标跟踪事件
 * \param b true 开启鼠标跟踪，false 关闭，且默认是关闭
 * \return 此时鼠标跟踪的状态： true 为开启，false 为关闭
 */
bool ScreenShots::DectionAndSetMouseTracking(bool b)
{
    m_mouseTracking = b;
    setMouseTracking(m_mouseTracking);
    return m_mouseTracking;
}

void ScreenShots::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        close();
}

void ScreenShots::mousePressEvent(QMouseEvent *event)
{
    DectionAndSetMouseTracking(false);

    if (m_rect.isEmpty())
        m_screenType = ScreenType::Select;

    PosType posType = isInArea(event->pos());
    switch (posType) {
    case PosType::Contains: {       // 点在矩形内部 (不含边界)
        m_screenType = ScreenType::Move;
        break;
    }
    case PosType::Cross: {         // 点在矩形边框上
        m_screenType = ScreenType::SetSize;
        break;
    }
    case PosType::External: {       // 点在矩形边框外部
        m_endPos = m_staPos = event->pos();
        m_screenType = ScreenType::Select;
        break;
    }
    case PosType::Other: {           // 矩形不存在, 暂时返回未知
        break;
    }
    default: {
        qDebug()<<"---应该不会被触发的情况";
        break;
    }
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
    isInArea(event->pos());
    if (m_mouseTracking) {
        qDebug()<<"---[mouseMove] 鼠标跟踪开启"<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
    } else {
        if (m_screenType == ScreenType::Select) {
            m_endPos = event->pos();
        } else if (m_screenType == ScreenType::Move){
            m_moveEndPos = event->pos();;
        }
        qDebug()<<"---[mouseMove] 鼠标跟踪关闭"<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);

    }

}

void ScreenShots::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_screenType == ScreenType::Select) {
        m_endPos = event->pos();
    } else if (m_screenType == ScreenType::Move){
        m_staPos = m_rect.topLeft();
        m_endPos = m_rect.bottomRight() + QPoint(1, 1);  // Qt 历史原因，所以要加 1 px
        m_moveEndPos = m_moveStaPos = QPoint(0, 0);
    }

    DectionAndSetMouseTracking(true);
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

//    qDebug()<<"---[paintEvent1]"<<m_staPos<<m_endPos<<m_rect<<"   "<<pos<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
//    qDebug()<<"---->"<< QApplication::desktop()->rect()<<m_pixmap->rect()<<m_basePixmap->rect()<<m_sysInfo->devicePixelRatio();
    if (!m_rect.isEmpty()) {
        pa.drawPixmap(m_rect, m_pixmap->copy(baseRect));
        drawScreenRect(m_rect, pa);
    }

//    int x1 = m_rect.x();
//    int y1 = m_rect.y();
//    int x2 = m_rect.x() + m_rect.width();
//    int y2 = m_rect.y() + m_rect.height();
//    int width = 8;
//    int w = 2 * width;
//    QRect rTopLeft(x1 - width, y1 - width, w, w);
//    QRect rTopRight(x2 - width, y1 - width, w, w);
//    QRect rBottomLeft(x1 - width, y2 - width, w, w);
//    QRect rBottomRight(x2 - width, y2 - width, w, w);
//    QRect rTop(x1 + width, y1 - width, m_rect.width() - w, w);
//    QRect rBottom(x1 + width, y2 - width, m_rect.width() - w, w);
//    QRect rLeft(x1 - width, y1 + width, w, m_rect.height() - w);
//    QRect rRight(x2 - width, y1 + width, w, m_rect.height() - w);

//    pa.fillRect(rTopLeft, Qt::red);
//    pa.fillRect(rTopRight, Qt::red);
//    pa.fillRect(rBottomLeft, Qt::yellow);
//    pa.fillRect(rBottomRight, Qt::yellow);
//    pa.fillRect(rTop, Qt::green);
//    pa.fillRect(rBottom, Qt::green);
//    pa.fillRect(rLeft, Qt::blue);
//    pa.fillRect(rRight, Qt::blue);

//    qDebug()<<"---[paintEvent2]"<<m_staPos<<m_endPos<<m_rect<<"   "<<pos<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
    update();
}

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
#include "toolboxwindow.h"

#define CURR_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz")

ScreenShots::ScreenShots()
{
    qDebug()<<"构造函数";
    init();
    m_sysInfo = new SystemInfo();
    m_toolBox = new ToolBoxWindow();
    m_toolBox->setParent(this);

    pixmap();      // 捕获原图和处理后的背景图
    basePixmap();
}

ScreenShots::~ScreenShots()
{
    delete m_pixmap;
    delete m_basePixmap;
    delete m_sysInfo;
}

/*!
 * \brief ScreenShots::instances 单例模式，唯一的构建方式
 * \return
 */
ScreenShots *ScreenShots::instances()
{
    static ScreenShots instances;  // 局部静态变量
    return &instances;
}

void ScreenShots::init()
{
    setObjectName("screenShots");
    setWindowTitle("ScreenShots");
    m_mouseTracking = false;
    m_cursor = false;
    m_translate = QPoint(0, 0);
    m_sizeMargins = QMargins(0, 0, 0, 0);
    QPoint posNull;
    m_rect = QRect();
    m_staPos = m_endPos = posNull;
    m_moveStaPos = m_moveEndPos = posNull;
    m_sizeStaPos = m_sizeEndPos = posNull;
    m_pixmap = m_basePixmap = nullptr;
    m_sysInfo = nullptr;
    m_screenType = ScreenType::Select;
    DectionAndSetMouseTracking(true);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);   // 窗口置顶 + 隐藏标题栏
    setFixedSize(QApplication::desktop()->rect().size());
//    setFixedSize(QSize(1600, 800));
//    setFixedSize(QGuiApplication::screenAt(QCursor::pos())->size());    // 用 resize() 的话，发现会操蛋的蛋疼

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
    blurPixmap.fill(QColor(255, 255, 255, 0.2 * 255));
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
 * \brief ScreenShots::drawAnchor 绘画矩形线框上面的八个锚点
 * \param pa 画家
 * \param b 是否绘画锚点
 * \param r 锚点的半径
 */
void ScreenShots::drawAnchor(QPainter &pa, bool b, int r)
{
    if (!b)
        return;
    pa.setRenderHint(QPainter::Antialiasing, false);
    int x1 = m_rect.left();
    int y1 = m_rect.top();
    int x2 = m_rect.right();
    int y2 = m_rect.bottom();  // 回看这里， 居然不是 + 1
    QVector<QPoint> ver = {QPoint(x1, y1),
                           QPoint(x2, y1),
                           QPoint(x1, y2),
                           QPoint(x2, y2),
                           QPoint((x1 + x2) / 2.0, y1),
                           QPoint((x1 + x2) / 2.0, y2),
                           QPoint(x1, (y1 + y2) / 2.0),
                           QPoint(x2, (y1 + y2) / 2.0)};

    pa.setPen(QPen(Qt::white, 1.5));
    pa.setBrush(QColor(146, 146, 146, 1 * 255));
    foreach (QPoint v, ver) {
        pa.drawEllipse(v, r, r);
    }
}

PosArrow ScreenShots::posArrow(QPoint pos, int width)
{
    if (m_rect.isEmpty() || width < 1)
        return PosArrow::UnKnown;;

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

    // 安装使用频率和习惯来进行优化
    if (rBottomRight.contains(pos, true))
        return PosArrow::BottomRight;
    else if (rBottom.contains(pos, true))
        return PosArrow::Bottom;
    else if (rRight.contains(pos, true))
        return PosArrow::Right;
    else if (rTopRight.contains(pos, true))
        return PosArrow::TopRight;
    else if (rBottomLeft.contains(pos, true))
        return PosArrow::BottomLeft;
    else if (rTop.contains(pos, true))
        return PosArrow::Top;
    else if (rLeft.contains(pos, true))
        return PosArrow::Left;
    else if (rTopLeft.contains(pos, true))
        return PosArrow::TopLeft;
    else
        return PosArrow::UnKnown;
}

/*!
 * \brief ScreenShots::isInArea 检测当前鼠标所处矩形的位置
 * \param[in] pos 检测某点是否在矩形中的点
 */
PosType ScreenShots::isInArea(QPoint pos, int width)
{
    if (m_rect.isEmpty() || m_cursor)
        return PosType::Other;

    int w = 2 * width;
    QRect outboard(m_rect.x() - width, m_rect.y() - width, m_rect.width() + w, m_rect.height() + w);  // 外侧矩形
    QRect inside(m_rect.x() + width, m_rect.y() + width, m_rect.width() - w, m_rect.height() - w);    // 内侧矩形

    if (outboard.contains(pos, true)) {
        if (inside.contains(pos, true)) {  // 点在矩形内部（不含边界）
//            qDebug()<<"--c--"<<pos<<"点在矩形内部";
            setCursor(Qt::SizeAllCursor);
            return PosType::Contains;
        } else {                           // 点在矩形边界上
//            qDebug()<<"--c--"<<pos<<"点在矩形边界上";
            if (m_mouseTracking)
                updateCursor(pos, width);
            return PosType::Cross;
        }
    } else {                                // 点在矩形外部（不含边界）
//        qDebug()<<"--c--"<<pos<<"点在矩形外部（不含边界）";
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

/*!
 * \brief ScreenShots::rootRect 获取操作系统分辨率下的矩形大小
 * \return 操作系统分辨率下的矩形大小
 */
QRect ScreenShots::rootRect()
{
    return m_rect;
}

/*!
 * \brief ScreenShots::baseRect 获取物理分辨率下实际矩形大小
 * \return 物理分辨率下实际矩形大小
 */
QRect ScreenShots::baseRect()
{
    return QRect(m_rect.topLeft() * m_sysInfo->devicePixelRatio(), m_rect.size() * m_sysInfo->devicePixelRatio());
}

/*!
 * \brief ScreenShots::savePixmap 获取实际保存的截图
 * \return 保存的截图
 */
QPixmap ScreenShots::savePixmap()
{
    return m_pixmap->copy(baseRect());
}

void ScreenShots::keyPressEvent(QKeyEvent *event)
{
    const int Grow = 10;
    if (event->key() == Qt::Key_Escape) {
        close();
        qDebug()<<"---Key_Escape---";
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
        m_translate.setY(m_translate.y() - Grow);
    } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
        m_translate.setY(m_translate.y() + Grow);
    } else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        m_translate.setX(m_translate.x() - Grow);
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        m_translate.setX(m_translate.x() + Grow);
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Up) {
        m_sizeMargins.setTop(m_sizeMargins.top() + Grow);
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Down) {
        m_sizeMargins.setBottom(m_sizeMargins.bottom() + Grow);
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Left) {
        m_sizeMargins.setLeft(m_sizeMargins.left() + Grow);
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Right) {
        m_sizeMargins.setRight(m_sizeMargins.right() + Grow);
    } else if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Up) {
        m_sizeMargins.setTop(m_sizeMargins.top() - Grow);
    } else if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Down) {
        m_sizeMargins.setBottom(m_sizeMargins.bottom() - Grow);
    } else if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Left) {
        m_sizeMargins.setLeft(m_sizeMargins.left() - Grow);
    } else if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Right) {
        m_sizeMargins.setRight(m_sizeMargins.right() - Grow);
    }
}

void ScreenShots::mousePressEvent(QMouseEvent *event)
{
    DectionAndSetMouseTracking(false);

    if (m_rect.isEmpty())
        m_screenType = ScreenType::Select;

    PosType posType = isInArea(event->pos());
    m_cursor = true;
    switch (posType) {
    case PosType::Contains:       // 点在矩形内部 (不含边界)
        m_screenType = ScreenType::Move;
        break;
    case PosType::Cross:         // 点在矩形边框上
        m_screenType = ScreenType::SetSize;
        break;
    case PosType::External:       // 点在矩形边框外部
        m_endPos = m_staPos = event->pos();
        m_screenType = ScreenType::Select;
        break;
    case PosType::Other:           // 矩形不存在, 暂时返回未知
        break;
    default:
        qDebug()<<"---应该不会被触发的情况";
        break;
    }

    if (m_screenType == ScreenType::Select) {
        m_endPos = m_staPos = event->pos();
    } else if (m_screenType == ScreenType::Move) {
        m_moveEndPos = m_moveStaPos = event->pos();
    } else if (m_screenType == ScreenType::SetSize) {
        m_sizeEndPos = m_sizeStaPos = event->pos();
    }

    qDebug()<<"---[mousePress] 鼠标跟踪关闭"<<m_screenType<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "
           <<m_moveStaPos<<m_moveEndPos<<"   "
          <<m_sizeStaPos<<m_sizeEndPos<<(m_sizeEndPos - m_sizeStaPos)<<QString::number(m_screenType, 10);
}

void ScreenShots::mouseMoveEvent(QMouseEvent *event)
{
    isInArea(event->pos());
    if (m_mouseTracking) {
        qDebug()<<"---[mouseMove] 鼠标跟踪开启"<<m_screenType<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "
               <<m_moveStaPos<<m_moveEndPos<<"   "
              <<m_sizeStaPos<<m_sizeEndPos<<(m_sizeEndPos - m_sizeStaPos)<<QString::number(m_screenType, 10);
    } else {
        if (m_screenType == ScreenType::Select) {
            m_endPos = event->pos();
            m_sizeEndPos = m_sizeStaPos = QPoint(0, 0);
        } else if (m_screenType == ScreenType::Move){
            m_moveEndPos = event->pos();
            m_sizeEndPos = m_sizeStaPos = QPoint(0, 0);
        } else if (m_screenType == ScreenType::SetSize) {
            m_sizeEndPos = event->pos();
        }
        qDebug()<<"---[mouseMove] 鼠标跟踪关闭"<<m_screenType<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "
               <<m_moveStaPos<<m_moveEndPos<<"   "
              <<m_sizeStaPos<<m_sizeEndPos<<(m_sizeEndPos - m_sizeStaPos)<<QString::number(m_screenType, 10);
    }
}

void ScreenShots::mouseReleaseEvent(QMouseEvent *event)
{
    m_cursor = false;
    if (m_screenType == ScreenType::Select) {
        m_endPos = event->pos();
    } else if (m_screenType == ScreenType::Move){
        m_staPos = m_rect.topLeft();
        m_endPos = m_rect.bottomRight() + QPoint(1, 1);  // Qt 历史原因，所以要加 1 px
        m_moveEndPos = m_moveStaPos = QPoint(0, 0);
    } else if(m_screenType == ScreenType::SetSize) {
        m_staPos = m_rect.topLeft();
        m_endPos = m_rect.bottomRight() + QPoint(1, 1);
        m_sizeEndPos = event->pos();
    }

    DectionAndSetMouseTracking(true);
    qDebug()<<"---[mouseRelease]"<<m_screenType<<m_staPos<<m_endPos<<m_rect<<"   "<<event->pos()<<"   "
           <<m_moveStaPos<<m_moveEndPos<<"   "
          <<m_sizeStaPos<<m_sizeEndPos<<(m_sizeEndPos - m_sizeStaPos)<<QString::number(m_screenType, 10);
}

void ScreenShots::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!m_pixmap)
        return;

    QPainter pa(this);
    pa.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);   // 抗锯齿 + 平滑边缘处理

    setCurrRect();
    m_rect += m_sizeMargins;
    m_rect.translate(m_translate);

    QPoint pos = m_sizeEndPos - m_sizeStaPos;
    if ((!pos.isNull()) && (m_screenType == ScreenType::SetSize)) {
        switch (posArrow(m_sizeStaPos)) {
        case PosArrow::BottomRight:
            m_rect.setBottomRight(m_rect.bottomRight() + pos);
            break;
        case PosArrow::Bottom:
            m_rect.setBottom(m_rect.bottom() + 1 + pos.y());
            break;
        case PosArrow::Right:
            m_rect.setRight(m_rect.right() + 1 + pos.x());
            break;
        case PosArrow::TopRight:
            m_rect.setTopRight(m_rect.topRight() + QPoint(1, 0) + pos);
            break;
        case PosArrow::BottomLeft:
            m_rect.setBottomLeft(m_rect.bottomLeft() + QPoint(0, 1) + pos);
            break;
        case PosArrow::Top:
            m_rect.setTop(m_rect.top() + pos.y());
            break;
        case PosArrow::Left:
            m_rect.setLeft(m_rect.left() + pos.x());
            break;
        case PosArrow::TopLeft:
            m_rect.setTopLeft(m_rect.topLeft() + pos);
            break;
        default:
            qDebug()<<"----PosArrow::UnKnown---"<<pos;  // 实时检测 m_sizeStaPos（move 状态），要修改一下
            break;
        }
    }

    pos = offset();
    if ((!pos.isNull()) && (m_screenType == ScreenType::Move)) {
        m_rect.setTopLeft(m_rect.topLeft() + pos);
        m_rect.setBottomRight(m_rect.bottomRight() + pos);
    }


//    qDebug()<<"---[paintEvent1]"<<m_staPos<<m_endPos<<m_rect<<"   "<<pos<<"   "<<m_moveStaPos<<m_moveEndPos<<QString::number(m_screenType, 10);
//    qDebug()<<"---->"<< QApplication::desktop()->rect()<<m_pixmap->rect()<<m_basePixmap->rect()<<m_sysInfo->devicePixelRatio();
    pa.drawPixmap(QApplication::desktop()->rect(), *m_basePixmap);
    if (!m_rect.isEmpty()) {
        pa.drawPixmap(m_rect, m_pixmap->copy(baseRect()));  // baseRect() 后台选中矩形
        drawScreenRect(m_rect, pa);

        drawAnchor(pa);
    }

    m_toolBox->move(m_rect.right() - m_toolBox->width(), m_rect.bottom() + g_width + 1);
    if (m_rect.isValid())
        m_toolBox->show();
    else
        m_toolBox->hide();

    // 测试代码:
//    m_toolBox->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);   // 窗口置顶 + 隐藏标题栏
//    setWindowFlags(Qt::WindowStaysOnTopHint);
//    int x1 = m_rect.x();
//    int y1 = m_rect.y();
//    int x2 = m_rect.x() + m_rect.width();
//    int y2 = m_rect.y() + m_rect.height();
//    int width = g_width;
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

    update();
}

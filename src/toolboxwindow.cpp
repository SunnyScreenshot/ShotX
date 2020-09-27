#include "screenshots.h"
#include "toolboxwindow.h"

#include <QIcon>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QClipboard>
#include <QApplication>
#include <QDate>
#include <QFileDialog>

class screenshots;

#define CURR_TIME QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss")

/*!
 * \brief The ToolBoxWindow class 透明工具栏窗口，默认依附在截图窗口的右下角
 */

ToolBoxWindow::ToolBoxWindow()
{
    init();
}

void ToolBoxWindow::init()
{
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

    setContentsMargins(0, 0, 0, 0);
    QHBoxLayout   *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->setContentsMargins(4, 4, 4, 4);
    m_staPos = m_endPos = QPoint();

    var.fill(nullptr, 11);  // 初始化
    m_listName << "rectangle"
               << "ellipse"
               << "line"
               << "arrow"
               << "pen"
               << "text"
               << "mosaic"
               << "revoke"
               << "update"
               << "download"
               << "copy";

    QStringList listToolTip = {tr("矩形（⌘ + 1）")
                           , tr("椭圆（⌘ + 2）")
                           , tr("直线（⌘ + 3）")
                           , tr("箭头（⌘ + 4）")
                           , tr("笔（⌘ + 5）")
                           , tr("文字（⌘ + 6）")
                           , tr("模糊（⌘ + 7）")
                           , tr("撤销（⌘ + z）")
                           , tr("上传（⌃ + ⇧ + 1）")
                           , tr("保存（⌘ + s）")
                           , tr("复制到剪切板（return）") };

    for (int i = 0; i < m_listName.count(); ++i) {
        QString name = ":/icons/normal/" + m_listName[i] + ".svg";

        var[i] = new QToolButton();
        var[i]->setToolButtonStyle(Qt::ToolButtonIconOnly);
        var[i]->setAutoRaise(true); // 自动浮动模式
        var[i]->setIcon(QIcon(name));
        var[i]->setIconSize(QSize(16, 16));
        var[i]->setToolTip(listToolTip[i]);

        if (i < 7)
            var[i]->setCheckable(true);
        else
            var[i]->setCheckable(false);

        hBoxLayout->addWidget(var[i]);
    }

    connect(var[9], &QToolButton::released, this, &ToolBoxWindow::onDownload);
    connect(var[10], &QToolButton::released, this, &ToolBoxWindow::onCopy);
}

void ToolBoxWindow::mousePressEvent(QMouseEvent *event)
{
    m_endPos = m_staPos = event->globalPos();
    m_topLeftPos = pos();
}

void ToolBoxWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_staPos.isNull()) {
        m_endPos = event->globalPos();
        move(m_topLeftPos + m_endPos - m_staPos);
    }
}

void ToolBoxWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_endPos = m_staPos = QPoint();
}

void ToolBoxWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    updateToolBtnIcon();

    QPainter pa(this);
    pa.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    pa.setPen(Qt::NoPen);
    pa.setBrush(QColor(255, 255, 255, 0.7 * 255));

    const int round = 4;
    pa.drawRoundedRect(contentsRect().adjusted(1, 1, -1, -1), round, round);
}

/*!
 * \brief ToolBoxWindow::updateToolBtnIcon 依据 toolBtn 是否被按下，选用不同颜色 svg 图片
 */
void ToolBoxWindow::updateToolBtnIcon()
{
    for (int i = 0; i < var.count(); ++i) {
        QString normal = ":/icons/normal/" + m_listName[i] + ".svg";
        QString pressed = ":/icons/pressed/" + m_listName[i] + ".svg";

        if (var[i]->isChecked()) {
            var[i]->setIcon(QIcon(pressed));
        } else {
            var[i]->setIcon(QIcon(normal));
        }
    }
}

/*!
 * \brief ToolBoxWindow::onDownload 保存本地
 */
void ToolBoxWindow::onDownload()
{
    QString fileter = "图片文件(*.png);;图片文件(*.jpg);;所有文件(*.*)";
    QString fileNmae = QFileDialog::getSaveFileName(this, tr("保存图片"), "ShotX" + CURR_TIME + ".png", fileter);
    ScreenShots *screenShot = static_cast<ScreenShots *>(parent());
    screenShot->savePixmap().save( CURR_TIME + ".png");
    if (!fileNmae.isEmpty())
        screenShot->savePixmap().save( fileNmae);

    qDebug()<<"--------------onDownload"<<parent()<<parent()->parent()<<fileNmae;
}

/*!
 * \brief ToolBoxWindow::onCopy 点击复制，会将截图保存在剪切板上
 */
void ToolBoxWindow::onCopy()
{
    ScreenShots *screenShot = static_cast<ScreenShots *>(parent());
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(screenShot->savePixmap());
    qDebug()<<"--------------onCopy"<<parent()<<parent()->parent();
}



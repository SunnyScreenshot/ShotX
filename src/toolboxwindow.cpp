#include "toolboxwindow.h"

#include <QIcon>
#include <QToolButton>
#include <QHBoxLayout>
#include <QMouseEvent>

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
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->setContentsMargins(4, 4, 4, 4);
    m_staPos = m_endPos = QPoint();

    QVector<QToolButton *> var = {  toolBtnRect
                                  , toolBtnEllipse
                                  , toolBtnLine
                                  , toolBtnArrow
                                  , toolBtnPen
                                  , toolBtnText
                                  , toolBtnMosaic
                                  , toolBtnRevoke
                                  , toolBtnUpload
                                  , toolBtnDownload
                                  , toolBtnExit
                                  , toolBtnCopy };

    QStringList listName = {"rectangle"
                           , "ellipse"
                           , "line"
                           , "arrow"
                           , "pen"
                           , "text"
                           , "mosaic"
                           , "revoke"
                           , "update"
                           , "download"
                           , "exit"
                           , "copy" };

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
                           , tr("退出（esc）")
                           , tr("复制到剪切板（return）") };


    for (auto v = var.begin(); v != var.end(); ++v) {
        int i = var.indexOf(*v);
        QString name = ":/icons/normal/" + listName[i] + ".svg";

        *v = new QToolButton();
        (*v)->setToolButtonStyle(Qt::ToolButtonIconOnly);
        (*v)->setAutoRaise(true); // 自动浮动模式
        (*v)->setIcon(QIcon(name));
        (*v)->setIconSize(QSize(24, 24));
        (*v)->setToolTip(listToolTip[i]);
        (*v)->setCheckable(true);
        hBoxLayout->addWidget(*v);
    }

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



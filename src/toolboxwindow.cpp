#include "toolboxwindow.h"

#include <QAction>
#include <QIcon>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLine>
#include <QToolBar>
#include <QColor>
#include <QPalette>
#include <QPainter>

/*!
 * \brief The ToolBoxWindow class 透明工具栏窗口，默认依附在截图窗口的右下角
 */

ToolBoxWindow::ToolBoxWindow()
{
    init();


}

void ToolBoxWindow::init()
{
    setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->setContentsMargins(4, 4, 4, 4);

    toolBtnRect = new QToolButton();
    toolBtnRect->setIcon(QIcon(QPixmap(":/icons/normal/rectangle-normal.svg")));
    toolBtnEllipse = new QToolButton();
    toolBtnEllipse->setIcon(QIcon(":/icons/normal/ellipse-normal.svg"));
    toolBtnLine = new QToolButton();
    toolBtnLine->setIcon(QIcon(":/icons/normal/line-normal.svg"));
    toolBtnArrow = new QToolButton();
    toolBtnArrow->setIcon(QIcon(":/icons/normal/arrow-normal.svg"));
    toolBtnPen = new QToolButton();
    toolBtnPen->setIcon(QIcon(":/icons/normal/pen-normal.svg"));
    toolBtnText = new QToolButton();
    toolBtnText->setIcon(QIcon(":/icons/normal/text-normal.svg"));
    toolBtnBlurry = new QToolButton();
    toolBtnBlurry->setIcon(QIcon(":/icons/normal/blurry-normal.svg"));
    toolBtnRevoke = new QToolButton();
    toolBtnRevoke->setIcon(QIcon(":/icons/normal/revoke-normal.svg"));
    toolBtnUpload = new QToolButton();
    toolBtnUpload->setIcon(QIcon(":/icons/normal/update-normal.svg"));
    toolBtnSave = new QToolButton();
    toolBtnSave->setIcon(QIcon(":/icons/normal/save-normal.svg"));
    toolBtnQuit = new QToolButton();
    toolBtnQuit->setIcon(QIcon(QPixmap(":/icons/normal/quit-normal.svg")));
    toolBtnOk = new QToolButton();
    toolBtnOk->setIcon(QIcon(":/icons/normal/ok-normal.svg"));

    hBoxLayout->addWidget(toolBtnRect);
    hBoxLayout->addWidget(toolBtnEllipse);
    hBoxLayout->addWidget(toolBtnLine);
    hBoxLayout->addWidget(toolBtnArrow);
    hBoxLayout->addWidget(toolBtnPen);
    hBoxLayout->addWidget(toolBtnText);
    hBoxLayout->addWidget(toolBtnBlurry);
    hBoxLayout->addWidget(toolBtnRevoke);
    hBoxLayout->addWidget(toolBtnUpload);
    hBoxLayout->addWidget(toolBtnSave);
    hBoxLayout->addWidget(toolBtnQuit);
    hBoxLayout->addWidget(toolBtnOk);

    QToolBar *toolBar = new QToolBar("test tool bar");

//    setWindowOpacity(0.7);

//    QPalette pal = palette();


//    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));


//    setPalette(pal);
}

void ToolBoxWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.setCompositionMode( QPainter::CompositionMode_Clear );

    p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
}

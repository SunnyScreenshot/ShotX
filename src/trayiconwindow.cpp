#include "trayiconwindow.h"

//#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>

TrayIconWindow::TrayIconWindow()
{
    init();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayIconWindow::onActiveTray);
    connect(m_actMainWindow, &QAction::triggered, this, &TrayIconWindow::onActMainWindow);
}

TrayIconWindow::~TrayIconWindow()
{
    m_trayIcon->deleteLater();  // 后面仔细看下与 delete 的差异
}

void TrayIconWindow::init()
{

    m_menu = new QMenu();
    m_actMainWindow = new QAction(tr("配置")); // 显示主窗口
    m_actExit = new QAction(tr("退出"));       // 退出
    m_menu->addAction(m_actMainWindow);
    m_menu->addSeparator();
    m_menu->addAction(m_actExit);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/icons/logo.svg"));
    m_trayIcon->setToolTip(tr("ShotX"));
    m_trayIcon->setContextMenu(m_menu);
    m_trayIcon->show();
}

void TrayIconWindow::onActiveTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:    // 单击系统托盘
    case QSystemTrayIcon::DoubleClick:// 双击（在macOS上，仅在未设置上下文菜单的情况下才会发出双击，因为菜单是在鼠标按下时打开的）
        qDebug()<<"---单击或者双击---";

        break;
    case QSystemTrayIcon::Context:    // 请求系统托盘上下文菜单
        qDebug()<<"---请求上下文---";
        m_menu->show();
        break;
    default:
        break;
    }
}

void TrayIconWindow::onActMainWindow()
{
    qDebug()<<"---配置---";
    m_mainWindow = new MainWindow();
    m_mainWindow->show();
}

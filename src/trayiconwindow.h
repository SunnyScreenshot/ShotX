#ifndef TRAYICONWINDOW_H
#define TRAYICONWINDOW_H

#include <QSystemTrayIcon>
#include <QWidget>
#include "mainwindow.h"

//class QSystemTrayIcon;
class QMenu;
class QAction;

class TrayIconWindow : public QWidget
{
    Q_OBJECT
public:
    TrayIconWindow();
    ~TrayIconWindow();

    void init();

public slots:
    void onActiveTray(QSystemTrayIcon::ActivationReason reason);
    void onActMainWindow();

private:
    QMenu           *m_menu;
    QAction         *m_actMainWindow;
    QAction         *m_actExit;
    MainWindow      *m_mainWindow;
    QSystemTrayIcon *m_trayIcon;  // 托盘图标
};

#endif // TRAYICONWINDOW_H

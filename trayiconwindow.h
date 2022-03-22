#ifndef TRAYICONWINDOW_H
#define TRAYICONWINDOW_H

#include <QSystemTrayIcon>
#include <QWidget>
#include "mainwindow.h"
#include "about.h"

//class QSystemTrayIcon;
class QMenu;
class QAction;
class ScreenShots;

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
    void onAbout();
    void onCreateScreen();


protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QMenu           *m_menu;
//    QAction         *m_actMainWindow;
    MainWindow      *m_mainWindow;
    QAction         *m_actAbout;
    About           *m_aboutWindow;
    QAction         *m_actExit;
    QSystemTrayIcon *m_trayIcon;     // 托盘图标
    ScreenShots     *m_screenShot;
};

#endif // TRAYICONWINDOW_H

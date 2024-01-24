// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2020-2024 XMuli
// SPDX-GitHub: https://github.com/XMuli/shotx
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

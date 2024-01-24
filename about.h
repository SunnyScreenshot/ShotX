// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2020-2024 XMuli
// SPDX-GitHub: https://github.com/XMuli/shotx
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H

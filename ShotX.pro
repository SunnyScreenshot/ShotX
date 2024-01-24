# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: 2020-2024 XMuli
# SPDX-GitHub: https://github.com/XMuli/shotx
# SPDX-Author: XMuli <xmulitech@gmail.com>

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    GuiHelper/guiapplicationhelper.cpp \
    main.cpp \
    mainwindow.cpp \
    screenshots.cpp \
    systeminfo.cpp \
    toolboxwindow.cpp \
    trayiconwindow.cpp \
    about.cpp

HEADERS += \
    GuiHelper/guiapplicationhelper.h \
    mainwindow.h \
    screenshots.h \
    systeminfo.h \
    toolboxwindow.h \
    trayiconwindow.h \
    about.h

include(./3rdparty/QHotkey/qhotkey.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += Resources.qrc

FORMS += \
    about.ui

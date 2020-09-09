# 使用CMake的版本号
cmake_minimum_required(VERSION 3.5)

# 指定了项目名和所使用的编程语言
project(ShotX LANGUAGES CXX)

# Qt的Cmake配置，实现ui文件自动打包、自动moc预编译以及rc文件的自动打包
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)            # 指定c++的标准为c++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 寻找Qt的库文件
find_package(Qt5 COMPONENTS Widgets REQUIRED)


# 设置两个变量
set (SHOTX_HEADER_FILES
    mainwind.h
    screenshot.h
    screen.h
    )

set (SHOTX_CPP_FILES
    main.cpp
    mainwind.cpp
    screenshot.cpp
    screen.cpp
    )

set (SHOTX_QRC_FILES
    resources.qrc
    )

set (SHOTX_RC_FILES
    # it's empty
    )

set (MYPROJECT_NAME ShotX)


add_executable (${MYPROJECT_NAME}
    ${SHOTX_HEADER_FILES}
    ${SHOTX_CPP_FILES}
    ${SHOTX_QRC_FILES}
    ${SHOTX_RC_FILES}
    )


# 在可执行文件中进行链接
target_link_libraries(${MYPROJECT_NAME} Qt5::Widgets)

if (WIN32)
    # it's empty
elseif (UNIX)
    install (
        FILES icons/app-icon.svg
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/48x48/apps"
    )
endif()


# 添加链接指令(Windows)：
# 使用了一个链接指令来使在Windows平台编译后执行程序不是以控制台窗口的形式执行的，
# 而是以仅仅为窗口的形式打开。（即不会出现cmd的窗口) （仅对mingw编译器有效）
#if(WIN32)
#    add_link_options("-mwindows")
#endif()


#list(APPEND SOURCES $)







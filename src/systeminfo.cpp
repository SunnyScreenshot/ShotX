#include "systeminfo.h"

#include <QScreen>
#include <QApplication>

SystemInfo::SystemInfo()
{
    m_screen = QApplication::primaryScreen();    // 获取屏幕原始截图
    m_deskWid = QApplication::desktop();         // 获取桌面的窗体对象
}

/*!
 * \brief SystemInfo::logicalDPI 获取逻辑 DPI
 * \return 逻辑 DPI
 */
int SystemInfo::logicalDPI()
{
    return m_screen->logicalDotsPerInch();
}

/*!
 * \brief SystemInfo::physicalDPI 获取物理 DPI
 * \return 物理 DPI
 */
int SystemInfo::physicalDPI()
{
    return m_screen->physicalDotsPerInch();
}

/*!
 * \brief SystemInfo::devicePixelRatio 获取屏幕缩放比例
 * \return 屏幕缩放比
 */
int SystemInfo::devicePixelRatio()
{
    return m_screen->devicePixelRatio();
}

/*!
 * \brief SystemInfo::screenGeometry 获取设备屏幕大小
 * \return 设备屏幕大小
 */
QRect SystemInfo::screenGeometry()
{
    return m_deskWid->screenGeometry();
}

/*!
 * \brief SystemInfo::availableGeometry 获取可用桌面大小
 * \return 可用桌面大小
 */
QRect SystemInfo::availableGeometry()
{
    return m_deskWid->availableGeometry();
}

/*!
 * \brief SystemInfo::virtualGeometry 若是虚拟桌面开启，返回其分辨率
 * \param[out] rect 虚拟桌面开启，返回其分辨率
 * \param[out] b 为 true 则开启；为 false 则未开启
 */
void SystemInfo::virtualGeometry(QRect &rect, bool &b)
{
    rect = m_screen->virtualGeometry();
    b = m_deskWid->isVirtualDesktop();
}

/*!
 * \brief SystemInfo::globalScreen 获取屏幕的相关信息
 * \param[out] pix 屏幕截图原始图
 * \param[out] rect 原始截图的尺寸
 * \param[out] num 屏幕个数
 */
void SystemInfo::globalScreen(QPixmap *pix, QRect &rect, int num)
{

    pix = new QPixmap(m_screen->grabWindow(m_deskWid->winId(), 0, 0, m_deskWid->size().width(), m_deskWid->size().height()));  // 截取屏幕上窗体对象所在区域的图像
    rect = pix->rect();
    num = m_deskWid->screenCount();
}


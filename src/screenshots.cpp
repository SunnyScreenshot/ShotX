#include "screenshots.h"

ScreenShots::ScreenShots(QSize size)
{

}

void ScreenShots::init()
{
    QPoint posNull;
    m_rect = QRect();
    m_staPos = m_endPos = posNull;
    m_moveStaPos = m_moveEndPos = posNull;
    m_pixmap = m_basePixmap = m_savePixmap =nullptr;
}

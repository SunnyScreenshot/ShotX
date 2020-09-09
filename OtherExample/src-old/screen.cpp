#include "screen.h"

Screen::Screen()
{
    init();
}

Screen::Screen(QSize size)
{
    init();

    rect.setWidth(size.width());
    rect.setHeight(size.height());
}

void Screen::init()
{
    QPoint posNull(0, 0);
    staPos = curPos = endPos = posNull;
    moveStaPos = moveEndPos = posNull;
    status = Screen::select;
}

void Screen::setStaPos(QPoint pos)
{
    staPos = pos;
}

void Screen::setCurPos(QPoint pos)
{
    curPos = pos;
}

void Screen::setEndPos(QPoint pos)
{
    endPos = pos;
}

void Screen::setTopLeft(QPoint pos)
{
    rect.setTopLeft(pos);
}

void Screen::setTopLeft()
{
    QPoint pos;
    pos.setX(qMin(staPos.x(), curPos.x()));
    pos.setY(qMin(staPos.y(), curPos.y()));
    rect.setTopLeft(pos);
}

void Screen::setBottomRight(QPoint pos)
{
    rect.setBottomRight(pos);
}

void Screen::setBottomRight()
{
    QPoint pos;
    pos.setX(qMax(staPos.x(), curPos.x()));
    pos.setY(qMax(staPos.y(), curPos.y()));
    rect.setBottomRight(pos);
}

void Screen::setWidth(int width)
{
    rect.setWidth(width);
}

void Screen::setHeight(int height)
{
    rect.setHeight(height);
}

void Screen::setRect(QRect& rect)
{
    this->rect = rect;
}

void Screen::setRect(QPoint topLeft, QSize size)
{
    rect.setTopLeft(topLeft);
    rect.setSize(size);
}

const QPoint Screen::getStaPos()
{
    return staPos;
}

const QPoint Screen::getCurPos()
{
    return curPos;
}

const QPoint Screen::getEndPos()
{
    return endPos;
}

const int Screen::getWidth()
{
    return rect.width();
}

const int Screen::getHeight()
{
    return rect.height();
}

const QRect Screen::getRect()
{
    return rect;
}

Screen::StatusFlags Screen::getStatus()
{
    return status;
}

QPoint Screen::setOffSet()
{
    return QPoint(moveEndPos - moveStaPos);
}

void Screen::setStatus(Screen::StatusFlags sta)
{
    status = sta;
}

bool Screen::isInArea(QPoint pos)
{
    if (pos.x() > rect.left() && pos.x() < rect.right() && pos.y() > rect.top() && pos.y() < rect.bottom())
        return true;

    return false;
}

#include "mypoint.h"


MyPoint::MyPoint(const QPoint &pt, const QColor &color)
    : m_point(pt)
    , m_color(color)
{
}

//--------------------------------------------------------------------------

const QPoint &MyPoint::point() const noexcept
{
    return m_point;
}

//--------------------------------------------------------------------------

const QColor &MyPoint::color() const noexcept
{
    return m_color;
}

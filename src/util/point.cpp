#include <cmath>
#include "point.h"
#include "util/math.h"

/*!
    \class Point
    \brief Describes point with Cartesian coordinates (x and y).
    \note Documentation for most of this class methods can be found in Qt docs (see class QPoint).
*/

Point::Point()
    : m_x(0), m_y(0)
{
}

Point::Point(int x, int y)
    : m_x(x), m_y(y)
{
}

Point::Point(const Point &point)
    : m_x(point.m_x), m_y(point.m_y)
{
}

int Point::x() const
{
    return m_x;
}

void Point::setX(int x)
{
    m_x = x;
}

int Point::y() const
{
    return m_y;
}

void Point::setY(int y)
{
    m_y = y;
}

bool Point::isNull() const
{
    return (m_x == 0 && m_y == 0);
}

int &Point::rx()
{
    return m_x;
}

int &Point::ry()
{
    return m_y;
}

/*!
    Calculates lenght to point with coordinates \a x, \a y.
*/
double Point::lengthTo(int x, int y) const
{
    return sqrt(pow(m_x - x, 2) + pow(m_y - y, 2));
}

/*!
    \overload
    Calculates length to point \a point.
*/
double Point::lengthTo(const Point &point) const
{
    return lengthTo(point.x(), point.y());
}

/*!
    Returns manhattan-length to point \a point.
    \note Manhattan-length calculates as M_L = abs(x1 - x2) + abs(y1 - y2).
*/
int Point::manhattanLengthTo(const Point &point) const
{
    return Math::abs(m_x - point.m_x) + Math::abs(m_y - point.m_y);
}

Point &Point::operator+=(const Point &point)
{
    m_x += point.m_x;
    m_y += point.m_y;
    return *this;
}

Point &Point::operator-=(const Point &point)
{
    m_x -= point.m_x;
    m_y -= point.m_y;
    return *this;
}

Point &Point::operator*=(double factor)
{
    m_x = Math::round(m_x * factor);
    m_y = Math::round(m_y * factor);
    return *this;
}

Point &Point::operator/=(double divisor)
{
    m_x = Math::round(m_x / divisor);
    m_y = Math::round(m_y / divisor);
    return *this;
}

/* Global operators */

bool operator==(const Point &p1, const Point &p2)
{
    return (p1.m_x == p2.m_x && p1.m_y == p2.m_y);
}

bool operator!=(const Point &p1, const Point &p2)
{
    return (p1.m_x != p2.m_x || p1.m_y != p2.m_y);
}

const Point operator+(const Point &p1, const Point &p2)
{
    return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

const Point operator-(const Point &p1, const Point &p2)
{
    return Point(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

const Point operator-(const Point &point)
{
    return Point(-point.m_x, -point.m_y);
}

const Point operator*(const Point &point, double factor)
{
    return Point(Math::round(point.m_x * factor), Math::round(point.m_y * factor));
}

const Point operator*(double factor, const Point &point)
{
    return point * factor;
}

const Point operator/(const Point &point, double divisor)
{
    return Point(Math::round(point.m_x / divisor), Math::round(point.m_y / divisor));
}

std::ostream &operator<<(std::ostream &lhs, const Point &rhs)
{
    lhs << '(' << rhs.m_x << ';' << rhs.m_y << ')';
    return lhs;
}

#include "util/math.h"
#include "util/size.h"

/*!
    \class Size
    \brief Describes size of geometric object with integer dimensions.
    \note Documentation for most of this class methods can be found in Qt docs (see class QSize).
*/

Size::Size()
    : m_width(0), m_height(0)
{
}

Size::Size(int width, int height)
    : m_width(width), m_height(height)
{
}

Size::Size(const Size &size)
    : m_width(size.m_width), m_height(size.m_height)
{
}

int Size::width() const
{
    return m_width;
}

void Size::setWidth(int width)
{
    m_width = width;
}

int Size::height() const
{
    return m_height;
}

void Size::setHeight(int height)
{
    m_height = height;
}

void Size::setSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Size::setSize(const Size &size)
{
    setSize(size.m_width, size.m_height);
}

int &Size::rwidth()
{
    return m_width;
}

int &Size::rheight()
{
    return m_height;
}

/*!
    Returns area of size rectangle.
*/
int Size::area() const
{
    return m_width * m_height;
}

bool Size::isNull() const
{
    return (m_width == 0 && m_height == 0);
}

bool Size::isEmpty() const
{
    return (m_width <= 0 || m_height <= 0);
}

bool Size::isValid() const
{
    return (m_width > 0 && m_height > 0);
}

void Size::transpose()
{
    int tmp = m_width;
    m_width = m_height;
    m_height = tmp;
}

Size Size::boundedTo(const Size &otherSize) const
{
    int width = m_width <= otherSize.m_width ? m_width : otherSize.m_width;
    int height = m_height <= otherSize.m_height ? m_height : otherSize.m_height;
    return Size(width, height);
}

Size Size::expandedTo(const Size &otherSize) const
{
    int width = m_width >= otherSize.m_width ? m_width : otherSize.m_width;
    int height = m_height >= otherSize.m_height ? m_height : otherSize.m_height;
    return Size(width, height);
}

Size &Size::operator+=(const Size &size)
{
    m_width += size.m_width;
    m_height += size.m_height;
    return *this;
}

Size &Size::operator-=(const Size &size)
{
    m_width -= size.m_width;
    m_height -= size.m_height;
    return *this;
}

Size &Size::operator*=(double factor)
{
    m_width = Math::round(m_width * factor);
    m_height = Math::round(m_height * factor);
    return *this;
}

Size &Size::operator/=(double divisor)
{
    m_width = Math::round(m_width / divisor);
    m_height = Math::round(m_height / divisor);
    return *this;
}

/* Global operators */

bool operator==(const Size &s1, const Size &s2)
{
    return (s1.m_width == s2.m_width && s1.m_height == s2.m_height);
}

bool operator!=(const Size &s1, const Size &s2)
{
    return (s1.m_width != s2.m_width || s1.m_height != s2.m_height);
}

const Size operator+(const Size &s1, const Size &s2)
{
    return Size(s1.m_width + s2.m_width, s1.m_height + s2.m_height);
}

const Size operator-(const Size &s1, const Size &s2)
{
    return Size(s1.m_width - s2.m_width, s1.m_height - s2.m_height);
}

const Size operator*(const Size &size, double factor)
{
    return Size(Math::round(size.m_width * factor), Math::round(size.m_height * factor));
}

const Size operator*(double factor, const Size &size)
{
    return size * factor;
}

const Size operator/(const Size &size, double divisor)
{
    return Size(Math::round(size.m_width / divisor), Math::round(size.m_height / divisor));
}

std::ostream &operator<<(std::ostream &lhs, const Size &rhs)
{
    lhs << '(' << rhs.m_width << ';' << rhs.m_height << ')';
    return lhs;
}

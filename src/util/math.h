#ifndef MATH_H
#define MATH_H

#include <cstdlib>

namespace Math {

/*!
    Returns absolute value if \a value.
*/
template <typename T>
inline T abs(const T &value)
{
    if (value >= 0)
        return value;
    return -value;
}

/*!
    Returns minimal value of \a value1 and \a value2.
    \note For type \a T must be provided operator "less than" (operator<).
*/
template <typename T>
inline const T &min(const T &value1, const T &value2)
{
    if (value1 < value2)
        return value1;
    return value2;
}

/*!
    Returns maximal value of \a value1 and \a value2.
    \note For type \a T must be provided operator "less than" (operator<).
*/
template <typename T>
inline const T &max(const T &value1, const T &value2)
{
    if (value1 < value2)
        return value2;
    return value1;
}

/*!
    Returns rounded value.
    \note See also http://www.cplusplus.com/forum/articles/3638/
*/
inline int round(double value)
{
    if (value >= 0.0)
        return int(value + 0.5);
    else
        return int(value - int(value - 1) + 0.5) + int(value - 1);
}

/*!
    Makes fuzzy compare of floating numbers \a value1 and \a value2.
    Returns true if these numbers fuzzy equal.
*/
inline bool fuzzyCompare(double value1, double value2)
{
    return (abs(value1 - value2) <= 1e-12 * min(abs(value1), abs(value2)));
}

/*!
    Calculates index of two-dimensions array that contains in one-dimensions array.
*/
inline int calcIndex(int x, int y, int width)
{
    return x + y * width;
}

} // namespace Math

#endif // MATH_H

#ifndef POINT_H
#define POINT_H

#include <ostream>

class Point
{
public:
    Point();
    Point(int x, int y);
    Point(const Point &point);

    int x() const;
    void setX(int x);
    int y() const;
    void setY(int y);

    bool isNull() const;

    int &rx();
    int &ry();

    double lengthTo(int x, int y) const;
    double lengthTo(const Point &point) const;
    int manhattanLengthTo(const Point &point) const;

    Point &operator+=(const Point &point);
    Point &operator-=(const Point &point);
    Point &operator*=(double factor);
    Point &operator/=(double divisor);

    friend bool operator==(const Point &p1, const Point &p2);
    friend bool operator!=(const Point &p1, const Point &p2);
    friend const Point operator+(const Point &p1, const Point &p2);
    friend const Point operator-(const Point &p1, const Point &p2);
    friend const Point operator-(const Point &point);
    friend const Point operator*(const Point &point, double factor);
    friend const Point operator*(double factor, const Point &point);
    friend const Point operator/(const Point &point, double divisor);
    friend std::ostream &operator<<(std::ostream &lhs, const Point &rhs);

private:
    int m_x;
    int m_y;
};

#endif // POINT_H

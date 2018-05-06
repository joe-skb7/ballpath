#ifndef SIZE_H
#define SIZE_H

#include <ostream>

class Size
{
public:
    Size();
    Size(int width, int height);
    Size(const Size &size);

    int width() const;
    void setWidth(int width);
    int height() const;
    void setHeight(int height);
    void setSize(int width, int height);
    void setSize(const Size &size);
    int &rwidth();
    int &rheight();
    int area() const;

    bool isNull() const;
    bool isEmpty() const;
    bool isValid() const;

    void transpose();
    Size boundedTo(const Size &otherSize) const;
    Size expandedTo(const Size &otherSize) const;

    Size &operator+=(const Size &size);
    Size &operator-=(const Size &size);
    Size &operator*=(double factor);
    Size &operator/=(double divisor);

    friend bool operator==(const Size &s1, const Size &s2);
    friend bool operator!=(const Size &s1, const Size &s2);
    friend const Size operator+(const Size &s1, const Size &s2);
    friend const Size operator-(const Size &s1, const Size &s2);
    friend const Size operator*(const Size &size, double factor);
    friend const Size operator*(double factor, const Size &size);
    friend const Size operator/(const Size &size, double divisor);
    friend std::ostream &operator<<(std::ostream &lhs, const Size &rhs);

private:
    int m_width;
    int m_height;
};

#endif // SIZE_H

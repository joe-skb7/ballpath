#ifndef ACTION_H
#define ACTION_H

#include "util/point.h"

/*!
    \struct Action
    \brief Represents one step at game map. Stores type of step and it point coordinates.
*/

struct Action
{
    enum Type { Undefined = 0, Left = 1, Right = 2, Up = 3, Down = 4, Finish = 5 };

    Type type;
    Point point;

    explicit Action(Type type = Undefined, const Point &point = Point())
        : type(type), point(point)
    {
    }
};

#endif // ACTION_H

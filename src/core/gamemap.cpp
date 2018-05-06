#include <iostream>
#include "core/gamemap.h"
#include "util/math.h"

/*!
    \class GameMap
    \brief Represents game map as two-dimensions array of nodes.
    \sa Node, PathFinder
*/

/*!
    Constructs empty game map; to resize it later use method \a resize().
*/
GameMap::GameMap()
{
}

/*!
    Constructs game map with size \a size and links all the nodes with their neighbours at once.
*/
GameMap::GameMap(const Size &size)
    : m_size(size)
{
    resize(size);
}

/*!
    Constructs game map with size \a width, \a height and links all the nodes with their neighbours
    at once.
*/
GameMap::GameMap(int width, int height)
    : m_size(width, height)
{
    resize(m_size);
}

GameMap::~GameMap()
{
    for (auto v : m_map)
        delete v;
}

/*!
    Resizes game map area to \a size and relinks all the nodes with their neighbours.
*/
void GameMap::resize(const Size &size)
{
    m_size = size;
    for (auto v : m_map)
        delete v;
    m_map.resize(size.area());

    for (int j = 0; j < size.height(); ++j)
        for (int i = 0; i < size.width(); ++i)
            m_map[Math::calcIndex(i, j, m_size.width())] = new Node(i, j);

    // Linking
    for (int j = 0; j < size.height(); ++j) {
        for (int i = 0; i < size.width(); ++i) {
            if (i > 0)
                at(i, j)->l = at(i - 1, j);
            if (i < size.width() - 1)
                at(i, j)->r = at(i + 1, j);
            if (j > 0)
                at(i, j)->u = at(i, j - 1);
            if (j < size.height() - 1)
                at(i, j)->d = at(i, j + 1);
        }
    }
}

/*!
    Returns the dimensions of game map.
*/
Size GameMap::size() const
{
    return m_size;
}

/*!
    Returns node in game map that placed at \a x, \a y coordinates.
    \note This method is constant.
*/
const Node * const GameMap::at(int x, int y) const
{
    return m_map.at(Math::calcIndex(x, y, m_size.width()));
}

/*!
    Returns node in game map that placed at \a point coordinates.
    \note This method is constant.
*/
const Node * const GameMap::at(const Point &point) const
{
    return m_map.at(Math::calcIndex(point.x(), point.y(), m_size.width()));
}

/*!
    Returns node in game map that placed at \a x, \a y coordinates.
*/
Node * const GameMap::at(int x, int y)
{
    return m_map[Math::calcIndex(x, y, m_size.width())];
}

/*!
    Returns node in game map that placed at \a point coordinates.
*/
Node * const GameMap::at(const Point &point)
{
    return m_map[Math::calcIndex(point.x(), point.y(), m_size.width())];
}

/*!
    Returns the width dimension of game map (that also available through size().width()).
*/
int GameMap::width() const
{
    return m_size.width();
}

/*!
    Returns the height dimension of game map (that also available through size().height()).
*/
int GameMap::height() const
{
    return m_size.height();
}

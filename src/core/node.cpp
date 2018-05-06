#include "core/node.h"

/*!
    \struct Node
    \brief Represents one node in game map for A-Star algorithm.
    \sa GameMap, PathFinder
*/

Node::Node()
    : isWall(false)
{
    init();
}

Node::Node(bool isWall)
    : isWall(isWall)
{
    init();
}

Node::Node(int x, int y)
    : point(x, y), isWall(false)
{
    init();
}

/*!
    Returns iterator to begin position for iterate the neighbours.
*/
NodeIterator Node::begin()
{
    return NodeIterator(this);
}

/*!
    Returns iterator to end position for iterate the neighbours.
*/
NodeIterator Node::end()
{
    return NodeIterator(0);
}

/* private */

/*!
    Inits commonly used (in ctors) variables.
*/
void Node::init()
{
    parent = nullptr;
    l = r = u = d = nullptr;
    f = g = h = 0;
}

/* friends */

bool operator<(const Node &lhs, const Node &rhs)
{
    return lhs.f < rhs.f;
}

bool operator>(const Node &lhs, const Node &rhs)
{
    return lhs.f > rhs.f;
}

/*!
    \struct NodePtrLessComparator
    \brief Implements comparator for less-comparision (<) points to Node by it "f"-part.
*/

bool NodePtrLessComparator::operator()(const Node * const lhs, const Node * const rhs) const
{
    return lhs->f < rhs->f;
}

/*!
    \struct NodePtrGreaterComparator
    \brief Implements comparator for greater-comparision (>) points to Node by it "f"-part.
*/

bool NodePtrGreaterComparator::operator()(const Node * const lhs, const Node * const rhs) const
{
    return lhs->f > rhs->f;
}

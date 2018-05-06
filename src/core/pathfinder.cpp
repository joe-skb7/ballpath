#include "core/pathfinder.h"

namespace {
    const int StepCost = 1;
} // anonymous namespace

/*!
    \class PathFinder
    \brief Implements A* (A-Star) algorithm for finding shortest path at game map.

    In a nutshell, A* is most effective algorithm for finding of optimal path.

    You can read about this algorithm at:\n
    \htmlonly
    <a href="http://www.policyalmanac.org/games/aStarTutorial.htm">A* Tutorial</a><br>
    <a href="http://en.wikipedia.org/wiki/A*_search_algorithm">A* at Wikipedia</a>
    \endhtmlonly
*/

/*!
    Constructs PathFinder object with all the input data.
    \param gm Game map that contains array of nodes with information about it type (wall or empty).
    \param start Start point, i.e. where moveable ball is placed.
    \param finish Destination point (where ball need to be moved).
*/
PathFinder::PathFinder(GameMap *gm, const Point &start, const Point &finish)
    : m_gameMap(gm), m_start(start), m_finish(finish)
{
}

/*!
    Starts finding the path.
    \return \a true if path found or \a false if there is no path for specified input data.
    \sa path()
*/
bool PathFinder::findPath()
{
    Node *startNode = m_gameMap->at(m_start);
    Node *finishNode = m_gameMap->at(m_finish);
    startNode->f = startNode->h = heuristicCostEstimate(m_start, m_finish);

    m_openList.push(startNode);

    while (!m_openList.empty()) {
        Node *x = m_openList.top();
        if (x == finishNode)
            return reconstructPath();

        m_openList.pop();
        m_closedList.insert(x);

        // Testing for each neighbour of x
        for (Node::iterator it = x->begin(); it != x->end(); ++it) {
            Node *y = *it;
            if (!y || y->isWall || y == startNode || m_closedList.find(y) != m_closedList.end())
                continue; // skip "zero" neighbours, walls, start point and closed-list neighbours

            // Calculating g(x) for processing neighbour
            int tentativeG = x->g + StepCost;
            bool tentativeIsBetter;

            if (!y->parent) { // if neighbour is not in open list yet
                m_openList.push(y);
                tentativeIsBetter = true;
            } else if (tentativeG < y->g) {
                tentativeIsBetter = true;
            } else {
                tentativeIsBetter = false;
            }

            // Updating fields of neighbour
            if (tentativeIsBetter) {
                // WARNING: potentially buggy place; need to manual rebuild heap
                //          as values changed via pointer (y->f = ...)
                y->parent = x;
                y->g = tentativeG;
                y->h = heuristicCostEstimate(y->point, m_finish);
                y->f = y->g + y->h;
                rebuildOpenList();
            }
        }
    }

    // Path not found
    return true;
}

/*!
    Returns finded path.
    \sa findPath()
*/
Path PathFinder::path() const
{
    return m_path;
}

/* private */

/*!
    Populates \a m_path variable (by parents, started with finish point).
    \return true if path found.
*/
bool PathFinder::reconstructPath()
{
    Node *startNode = m_gameMap->at(m_start);
    Node *curNode = m_gameMap->at(m_finish);
    Node *prevNode = nullptr;
    do {
        if (!curNode->parent && curNode != startNode)
            return false; // there is no path
        Action action(probeActionType(curNode, prevNode), curNode->point);
        m_path.push_front(action);
        prevNode = curNode;
        curNode = curNode->parent;
    } while (prevNode->parent != 0);

    return true;
}

/*!
    Returns estimated heuristical cost for path from \a p1 to \a p2.
*/
int PathFinder::heuristicCostEstimate(const Point &p1, const Point &p2) const
{
    return p2.manhattanLengthTo(p1) * StepCost;
}

/*!
    Detects step direction from \a prev to \a cur.
*/
Action::Type PathFinder::probeActionType(const Node * const cur, const Node * const prev) const
{
    Node *finishNode = m_gameMap->at(m_finish);
    if (cur == finishNode)
        return Action::Finish;
    if (!cur || !prev)
        return Action::Undefined;

    if (cur->point.x() == prev->point.x() + 1)
        return Action::Left;
    if (cur->point.x() == prev->point.x() - 1)
        return Action::Right;
    if (cur->point.y() == prev->point.y() + 1)
        return Action::Up;
    if (cur->point.y() == prev->point.y() - 1)
        return Action::Down;

    return Action::Undefined;
}

/*!
    Initiates rebuilding of inner heap for open list.
*/
void PathFinder::rebuildOpenList()
{
    Node *tmp = new Node;
    tmp->f = -1;
    m_openList.push(tmp);
    m_openList.pop();
}

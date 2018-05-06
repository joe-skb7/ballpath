#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <queue>
#include <unordered_set>
#include "util/point.h"
#include "core/gamemap.h"
#include "core/path.h"

class PathFinder
{
public:
    PathFinder(GameMap *gm, const Point &start, const Point &finish);

    bool findPath();
    Path path() const;

private:
    GameMap *m_gameMap;
    Point m_start;
    Point m_finish;

    std::unordered_set<Node*> m_closedList;
    std::priority_queue<Node*, std::vector<Node*>, NodePtrGreaterComparator> m_openList;
    Path m_path;

    PathFinder(); // forbidden
    PathFinder(const PathFinder &); // forbidden
    PathFinder &operator=(const PathFinder &); // forbidden

    bool reconstructPath();
    int heuristicCostEstimate(const Point &p1, const Point &p2) const;
    Action::Type probeActionType(const Node * const cur, const Node * const prev) const;
    void rebuildOpenList();
};

#endif // PATHFINDER_H

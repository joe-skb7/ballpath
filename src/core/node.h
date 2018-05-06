#ifndef NODE_H
#define NODE_H

#include "util/point.h"
#include "core/nodeiterator.h"

struct Node
{
    Point point; //!< Node coordinates.
    Node *parent; //!< Node parent (see A-Star algorithm).
    Node *l, *r, *u, *d; //!< Links for left, right, up and down neighbours.
    bool isWall; //!< Contains true if this node is wall (ball); default is false.
    int f; //!< Contains full path estimation (see A-Star algorithm).
    int g; //!< Contains passed steps weight. (see A-Star algorithm).
    int h; //!< Contains heuristic estimate of retained path (see A-Star algorithm).

    Node();
    explicit Node(bool isWall);
    Node(int x, int y);

    typedef NodeIterator iterator;

    NodeIterator begin();
    NodeIterator end();

    friend bool operator<(const Node &lhs, const Node &rhs);
    friend bool operator>(const Node &lhs, const Node &rhs);
    friend class NodeIterator;
    friend struct NodePtrLessComparator;
    friend struct NodePtrGreaterComparator;

private:
    void init();
};

struct NodePtrLessComparator : public std::binary_function<const Node*, const Node*, bool>
{
    bool operator()(const Node * const lhs, const Node * const rhs) const;
};

struct NodePtrGreaterComparator : public std::binary_function<const Node*, const Node*, bool>
{
    bool operator()(const Node * const lhs, const Node * const rhs) const;
};

#endif // NODE_H

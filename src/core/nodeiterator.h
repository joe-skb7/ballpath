#ifndef NODEITERATOR_H
#define NODEITERATOR_H

class Node;

class NodeIterator
{
public:
    enum Neighbour { Unknown = 0, Left = 1, Right = 2, Up = 3, Down = 4 };

public:
    NodeIterator(Node *node);

    Node *operator*();
    Node *operator->();
    void operator++();
    NodeIterator operator++(int);
    bool operator==(const NodeIterator &i);
    bool operator!=(const NodeIterator &i);

    Neighbour currentNeighbour() const;

private:
    Node *m_node;
    Neighbour m_curNeighbour;

    Node *get() const;
};

#endif // NODEITERATOR_H

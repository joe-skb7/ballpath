#include "core/nodeiterator.h"
#include "core/node.h"

/*!
    \class NodeIterator
    \brief Implements iterator for iterating neighbours of Node.
*/

NodeIterator::NodeIterator(Node *node)
    : m_node(node), m_curNeighbour(Left)
{
}

Node *NodeIterator::operator*()
{
    return get();
}

Node *NodeIterator::operator->()
{
    return get();
}

void NodeIterator::operator++()
{
    if (!m_node)
        return;
    if (m_curNeighbour == Down) {
        m_curNeighbour = Unknown;
        m_node = nullptr;
    }

    m_curNeighbour = (Neighbour)(m_curNeighbour + 1);
}

NodeIterator NodeIterator::operator++(int)
{
    NodeIterator iter(*this);
    ++(*this);
    return iter;
}

bool NodeIterator::operator==(const NodeIterator &i)
{
    return m_node == i.m_node && m_curNeighbour == i.m_curNeighbour;
}

bool NodeIterator::operator!=(const NodeIterator &i)
{
    return !(*this == i);
}

NodeIterator::Neighbour NodeIterator::currentNeighbour() const
{
    return m_curNeighbour;
}

/* private */

Node *NodeIterator::get() const
{
    switch (m_curNeighbour) {
        case Left:
            return m_node->l;
        case Right:
            return m_node->r;
        case Up:
            return m_node->u;
        case Down:
            return m_node->d;
        default:
            return nullptr;
    }
}

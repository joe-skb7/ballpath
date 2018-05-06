#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "util/size.h"
#include "core/node.h"

class GameMap
{
public:
    GameMap();
    explicit GameMap(const Size &size);
    GameMap(int width, int height);
    ~GameMap();

    void resize(const Size &size);
    Size size() const;
    const Node * const at(int x, int y) const;
    const Node * const at(const Point &point) const;
    Node * const at(int x, int y);
    Node * const at(const Point &point);
    int width() const;
    int height() const;

private:
    Size m_size;
    std::vector<Node*> m_map;
};

#endif // GAMEMAP_H

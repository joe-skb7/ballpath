#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <fstream>
#include <string>
#include "core/gamemap.h"
#include "util/point.h"

class InputReader
{
public:
    InputReader();
    ~InputReader();

    bool read(const std::string &filePath);
    std::string errorString() const;

    Point startPoint() const;
    Point finishPoint() const;
    GameMap *gameMap() const;

private:
    std::ifstream m_file;
    mutable std::string m_errorString;
    Point m_start;
    Point m_finish;
    GameMap *m_gameMap;

    void skipNonNum();
    bool readGameMapSize();
    bool readStartPoint();
    bool readFinishPoint();
    bool readGameMapContent();
    bool validatePointBounds(const Point &p) const;
};

#endif // INPUTREADER_H

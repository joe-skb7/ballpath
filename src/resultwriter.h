#ifndef RESULTWRITER_H
#define RESULTWRITER_H

#include <string>
#include "core/gamemap.h"
#include "core/path.h"

class ResultWriter
{

public:
    static bool write(const GameMap &gameMap, const Path &path);

private:
    ResultWriter();

    static char actionChar(Action::Type actionType);
    static std::string makePathString(const Path &path);
    static std::string makeSolveMap(const GameMap &gameMap, const Path &path);
};

#endif // RESULTWRITER_H

#include <iostream>
#include "resultwriter.h"

namespace {
    const char ActionCharArr[] = { '?', 'L', 'R', 'U', 'D', 'F' };
    const char WallChar = 'O';
    const char EmptyChar = ' ';
} // anonymous namespace

/*!
    \class ResultWriter
    \brief Provides simply way to print out formatted result on the screen.

    \b Output \b format.

    1. If path not found then "There is no path" line appears.\n
    2. If path found then next entities will be printed out:
       - Shortest path: it's a sequence of steps that need to be acted to reach the destination
         point (in format "L, R, U, D" where L is left, R is right, U is up and D is down).
       - Steps number in path: count of steps as integer number.
       - Solve map: two-dimensions array of chars, where each char can be:
         - one of move chars (which mentioned above)
         - ball: 'O' character
         - empty cell: ' ' (whitespace) character
         - finish point: 'F' character
*/

/*!
    Writes out formatted result on the screen.
    \param gameMap Game field that needed for writing solve map.
    \param path Sequence of steps that needed for writing path and steps number.
*/
bool ResultWriter::write(const GameMap &gameMap, const Path &path)
{
    if (path.size() < 2) {
        std::cout << "There is no path" << std::endl;
    } else {
        std::cout << "Shortest path: " << makePathString(path) << std::endl;
        std::cout << "Steps number in path: " <<  path.size() - 1 << std::endl;
        std::cout << "Solve map:" << std::endl;
        std::cout << makeSolveMap(gameMap, path) << std::endl;
    }
    return true;
}

/* private */

char ResultWriter::actionChar(Action::Type actionType)
{
    return ActionCharArr[actionType];
}

std::string ResultWriter::makePathString(const Path &path)
{
    std::string res;
    if (path.empty())
        return res;

    for (auto v : path)
        res += actionChar(v.type) + std::string(", ");
    res.erase(res.size() - 5, 5);

    return res;
}

std::string ResultWriter::makeSolveMap(const GameMap &gameMap, const Path &path)
{
    std::string res;

    // Placing walls
    for (int j = 0; j < gameMap.size().height(); ++j) {
        for (int i = 0; i < gameMap.size().width(); ++i) {
            res.push_back(gameMap.at(i, j)->isWall ? WallChar : EmptyChar);
        }
        res.push_back('\n');
    }

    // Placing actions (moves)
    for (auto v : path) {
        res.replace(v.point.x() + (v.point.y()) * (gameMap.size().width() + 1), 1, 1,
                    actionChar(v.type));
    }

    return res;
}

#include "inputreader.h"

/*!
    \class InputReader
    \brief Reads input file with objective data and provides convenient access for it.

    \b Input \b file \b format.

    Line 1: rows count (one integer number).\n
    Line 2: columns count (one integer number).\n
    Line 3: start point coordinates with format "(x,y)" (without quotes).\n
    Line 4: finish point coordinates with format "(x,y)" (without quotes).\n
    Line 5 (et seq.): initial game map, where 0 is empty cell and 1 is ball ("wall" field).\n

    Input file example:
    \code
    7
    4
    (0,0)
    (2,5)
    1000
    0101
    0100
    0010
    0000
    0000
    1001
    \endcode
*/

InputReader::InputReader()
    : m_start(-1, -1), m_finish(-1, -1), m_gameMap(new GameMap)
{
}

InputReader::~InputReader()
{
    delete m_gameMap;
}

/*!
    Reads all the input data from \a filePath file.
    \return true if operation finished successfully.
    \sa errorString()
*/
bool InputReader::read(const std::string &filePath)
{
    m_file.open(filePath, std::ios_base::in);

    if (!m_file.good()) {
        m_errorString = "Open file error: probably file doesn't exist";
        m_file.close();
        return false;
    }

    if (!(readGameMapSize() && readStartPoint() && readFinishPoint() && readGameMapContent())) {
        m_file.close();
        return false;
    }

    // Transform to inner coordinate system (inverted Y-axis)
    m_start.ry() = m_gameMap->size().height() - 1 - m_start.ry();
    m_finish.ry() = m_gameMap->size().height() - 1 - m_finish.ry();

    m_file.close();
    return true;
}

/*!
    Returns last error text description.
    If there are no errors occurred -- returns empty string.
*/
std::string InputReader::errorString() const
{
    return m_errorString;
}

/*!
    Returns readed start position point (moveable ball position).
    \sa finishPoint(), gameMap()
*/
Point InputReader::startPoint() const
{
    return m_start;
}

/*!
    Returns readed finish position point (where ball need to be moved).
    \sa startPoint(), gameMap()
*/
Point InputReader::finishPoint() const
{
    return m_finish;
}

/*!
    Returns readed game map (as two-dimensional array that represents game field with balls).
    \sa startPoint(), finishPoint()
*/
GameMap *InputReader::gameMap() const
{
    return m_gameMap;
}

/* private */

void InputReader::skipNonNum()
{
    char c;
    while (m_file.get(c)) {
        if (isdigit(c)) {
            m_file.putback(c);
            break;
        }
    }
}

bool InputReader::readGameMapSize()
{
    if (m_file.eof()) {
        m_errorString = "EOF reached when reading game map dimensions";
        return false;
    }

    Size size(-1, -1);
    m_file >> size.rheight();
    m_file >> size.rwidth();
    if (size.width() <= 0 || size.height() <= 0) {
        m_errorString = "Invalid map dimensions";
        return false;
    }
    m_gameMap->resize(size);

    return true;
}

bool InputReader::readStartPoint()
{
    if (m_file.eof()) {
        m_errorString = "EOF reached when reading start point";
        return false;
    }

    skipNonNum();
    m_file >> m_start.rx();
    skipNonNum();
    m_file >> m_start.ry();
    if (!validatePointBounds(m_start)) {
        m_errorString = "Invalid start point specified";
        return false;
    }
    return true;
}

bool InputReader::readFinishPoint()
{
    if (m_file.eof()) {
        m_errorString = "EOF reached when reading finish point";
        return false;
    }

    skipNonNum();
    m_file >> m_finish.rx();
    skipNonNum();
    m_file >> m_finish.ry();
    if (!validatePointBounds(m_finish)) {
        m_errorString = "Invalid finish point specified";
        return false;
    }
    return true;
}

bool InputReader::readGameMapContent()
{
    skipNonNum();
    char c;
    for (int j = 0; j < m_gameMap->size().height(); ++j) {
        for (int i = 0; i < m_gameMap->size().width(); ++i) {
            if (m_file.eof()) {
                m_errorString = "EOF reached when reading game map content";
                return false;
            }
            if (!m_file.get(c)) {
                m_errorString = "Unknown error occurred when reading game map content";
                return false;
            }

            switch (c) {
                case '0':
                    m_gameMap->at(i, j)->isWall = false;
                    break;
                case '1':
                    m_gameMap->at(i, j)->isWall = true;
                    break;
                default:
                    m_errorString = std::string("Invalid game map content; character \'")
                                    + c + std::string("\' found");
                    return false;
            }
        }
        skipNonNum();
    }

    return true;
}

bool InputReader::validatePointBounds(const Point &p) const
{
    return p.x() >= 0 && p.y() >= 0 && p.x() < m_gameMap->width() && p.y() < m_gameMap->height();
}

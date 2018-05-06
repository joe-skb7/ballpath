#include <iostream>
#include "appcontroller.h"
#include "inputreader.h"
#include "resultwriter.h"
#include "core/pathfinder.h"

/*!
    \class AppController
    \brief Provides collaboration for all main apllication objects.
*/

AppController::AppController()
{
}

/*!
    Executes the application.
    \param filePath Path to input file.
*/
bool AppController::exec(const std::string &filePath)
{
    // Reading input data
    InputReader reader;
    if (!reader.read(filePath)) {
        std::cerr << reader.errorString() << std::endl;
        return false;
    }

    // Validating input
    if (!reader.gameMap()->at(reader.startPoint())->isWall) {
        std::cerr << "Start point must be a ball" << std::endl;
        return false;
    }
    if (reader.gameMap()->at(reader.finishPoint())->isWall) {
        std::cerr << "Finish point must be empty (not a ball)" << std::endl;
        return false;
    }

    // Finding the path
    PathFinder finder(reader.gameMap(), reader.startPoint(), reader.finishPoint());
    if (!finder.findPath()) {
        std::cout << "There is no path" << std::endl;
        return true;
    }

    // Writing result
    if (!ResultWriter::write(*reader.gameMap(), finder.path())) {
        std::cerr << "Error occurred when writing result" << std::endl;
        return false;
    }

    return true;
}

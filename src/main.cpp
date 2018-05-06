#include <cstdlib>
#include <iostream>
#include "appcontroller.h"

/*!
    \mainpage BallPath
    Project for finding shortest way in games like ColorLines.

    \b Usage.

    ./ballpath input_file \n
      or \n
    ./ballpath input_file >output_file

    \b Input.

    Input data passes via file (\a input_file above).\n
    For input file format description see InputReader class synopsis.

    \b Output.

    Output data writes directly to console (can be redirected to file).\n
    For output data format see ResultWriter class synopsis.

    \b Exit \b code.

    0 -- successful finish \n
    1 -- some errors occurred (see console output for details)

    \b Algorithm.

    For path finding used algorithm called "A*" or "A-Star". \n
    For details see PathFinder class description.

    \note Projects written in C++ with using of C++11 standard features, so you
    have to use at least GCC 4.6 (or newer) or other compiler that supports main C++11 features.
*/

/*!
    Prints out usage of application.
*/
void printUsage()
{
#if defined(_WIN32) || defined(_WIN64)
    std::cout << "Usage: ballpath.exe <input_file>" << std::endl;
#else
    std::cout << "Usage: ./ballpath <input_file>" << std::endl;
#endif
}

/*!
    Entry point.
*/
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printUsage();
        return EXIT_FAILURE;
    }

    AppController app;
    if (!app.exec(argv[1]))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

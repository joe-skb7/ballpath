#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <string>

class AppController
{

public:
    AppController();

    bool exec(const std::string &filePath);
};

#endif // APPCONTROLLER_H

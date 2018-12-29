#ifndef REDARROW_APPLICATION_H
#define REDARROW_APPLICATION_H


#include "../Engine/GameEngine.h"

class Application
{
public:
    Application(int argc, char** argv);

    int execute();

private:
    GameEngine m_gameEngine;
};


#endif //REDARROW_APPLICATION_H

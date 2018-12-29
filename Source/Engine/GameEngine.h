#ifndef REDARROW_GAMEENGINE_H
#define REDARROW_GAMEENGINE_H

#include "StateManager.h"

class GameEngine
{
public:
    GameEngine();

    ~GameEngine();

    bool isRunning();

    void execute();

private:
    StateManager m_stateManager;
};


#endif //REDARROW_GAMEENGINE_H

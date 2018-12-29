#ifndef REDARROW_GAMEENGINE_H
#define REDARROW_GAMEENGINE_H

#include "StateManager.h"

class GameEngine
{
public:
    GameEngine(sf::VideoMode mode, const std::string& title);

    ~GameEngine();

    bool isRunning();

    void execute();

private:
    StateManager m_stateManager;
    sf::RenderWindow m_window;
};


#endif //REDARROW_GAMEENGINE_H

#include "GameEngine.h"

GameEngine::GameEngine()
{
    m_stateManager.initialize();
}

GameEngine::~GameEngine()
{
    m_stateManager.cleanup();
}

bool GameEngine::isRunning()
{
    return false;
}

void GameEngine::execute()
{

}

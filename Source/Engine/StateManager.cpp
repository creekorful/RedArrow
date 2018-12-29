#include "StateManager.h"

void StateManager::initialize()
{
    m_pActiveState = nullptr;
}

void StateManager::cleanup()
{

}

void StateManager::handleEvents(const sf::Event& event)
{
    if (m_pActiveState != nullptr)
    {
        m_pActiveState->handleEvents(event);
    }
}

void StateManager::update(const float dt)
{
    if (m_pActiveState != nullptr)
    {
        m_pActiveState->update(dt);
    }
}

void StateManager::draw(sf::RenderWindow& window)
{
    if (m_pActiveState != nullptr)
    {
        m_pActiveState->draw(window);
    }
}

void StateManager::setActiveState(GameState* pState)
{
    // todo cleanup ?
    m_pActiveState = pState;
}

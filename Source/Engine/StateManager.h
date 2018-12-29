#ifndef REDARROW_STATEMANAGER_H
#define REDARROW_STATEMANAGER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameState.h"

class StateManager
{
public:
    void initialize();

    void cleanup();

    void handleEvents(const sf::Event& event);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void setActiveState(GameState* pState);

private:
    GameState* m_pActiveState;
};


#endif //REDARROW_STATEMANAGER_H

#ifndef REDARROW_STATEMANAGER_H
#define REDARROW_STATEMANAGER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class StateManager
{
public:
    void initialize();

    void cleanup();

    void handleEvents(const sf::Event& event);

    void update(float dt);

    void draw(sf::RenderWindow& window);
};


#endif //REDARROW_STATEMANAGER_H

#ifndef REDARROW_GAMESTATE_H
#define REDARROW_GAMESTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class GameState
{
public:

    virtual void initialize() = 0;

    virtual void cleanup() = 0;

    virtual std::string title() const = 0;

    /*virtual void pause() = 0;

    virtual void resume() = 0;*/

    virtual void handleEvents(const sf::Event& event) = 0;

    virtual void update(float dt) = 0;

    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif //REDARROW_GAMESTATE_H

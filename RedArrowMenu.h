//
// Created by creekorful on 22/09/2015.
//

#ifndef SPACEINVADERS_SPACEINVADERSCONTROLLER_H
#define SPACEINVADERS_SPACEINVADERSCONTROLLER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

class RedArrowMenu
{
public:
    RedArrowMenu(sf::RenderWindow* window);
    ~RedArrowMenu();

private:
    sf::Music m_music;
};


#endif //SPACEINVADERS_SPACEINVADERSCONTROLLER_H

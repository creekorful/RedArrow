//
// Created by creekorful on 22/09/2015.
//

#ifndef SPACEINVADERSCONTROLLER_H
#define SPACEINVADERSCONTROLLER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class RedArrowSinglePlayer
{
public:
    RedArrowSinglePlayer(sf::RenderWindow* window);
    ~RedArrowSinglePlayer();

private:
    sf::SoundBuffer m_ennemiFireSongBuffer;
    sf::Sound m_ennemiFireSound;
    sf::SoundBuffer m_ennemiExplodeBuffer;
    sf::Sound m_ennemiExplodeSound;
    sf::Music m_ambientMusic;
    sf::Music m_winMusic;
    sf::SoundBuffer m_looseLifeBuffer;
    sf::Sound m_looseLifeSong;
    sf::SoundBuffer m_gotALootBuffer;
    sf::Sound m_gotALootSong;
};


#endif //SPACEINVADERSCONTROLLER_H

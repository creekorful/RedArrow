//
// Created by creekorful on 21/09/2015.
//

#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include "Ship.h"
#include "Projectile.h"



class PlayerShip : public Ship
{
public:
    PlayerShip(short life);
    sf::ConvexShape getConvexShape();
    void manangeEvent(int delta, int xLen, int yLen, sf::Time elapsedTime);
    void draw(sf::RenderWindow* window);
    std::vector<Projectile*> getShipProjectiles();
    void setPlayerProjectiles(std::vector<Projectile*> projectiles);
    sf::Int32 getFireCount();
    void setPlayerLife(short playerLife);
    short getPlayerLife();
    void applyLoot(int lootType, sf::Time currentTime);
    ~PlayerShip();

private:
    std::vector<Projectile*> m_shipProjectiles;
    sf::ConvexShape m_shipShape;
    float m_moveSpeed;
    float m_rotSpeed;
    short m_playerLife;
    float m_moveStep;
    float m_maxMoveSpeed;
    bool m_isSuperSpeedEnabled;
    bool m_isSuperFireEnabled;
    sf::Int32 m_fireDelay;
    sf::Int32 m_fireCount;
    sf::Time m_lastDelay;
    sf::Time m_superSpeedLaunchTime;
    sf::Time m_superFireLaunchTime;
    sf::Sound m_fireSound;
    sf::SoundBuffer m_fireSoundBuffer;
};


#endif //SPACEINVADERS_PLAYERSHIP_H

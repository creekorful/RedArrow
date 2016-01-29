#include <iostream>
#include "EnnemyShip.h"

EnnemyShip::EnnemyShip(sf::Vector2f spawnPos, float vitesse, sf::Color aColor, int point, int fireDelay, int shipDesign, float projectileSpeed, short lifeCount, int dropRate)
{
    m_rotSpeed = 0.25f;
    m_moveSpeed = vitesse;
    m_projectileSpeed = projectileSpeed;
    m_life = lifeCount;
    m_dropRate = dropRate;

    if(shipDesign == ShipType::arrowShip)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( 12.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f(- 6.f,  11.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f(- 6.f, -11.f));
    }

    else if(shipDesign == ShipType::speedSpeederShip)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( 12.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f(- 14.f,  11.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f(- 14.f, -11.f));
    }

    else if(shipDesign == ShipType::fireSpeedShip)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( -12.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f( 6.f,  12.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f( 6.f, -12.f));
    }

    else if(shipDesign == ShipType::sniperShip)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( -12.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f( 15.f,  12.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f( 15.f, -12.f));
    }

    else if(shipDesign == ShipType::ultraSpeed)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( 12.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f(- 6.f,  19.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f(- 6.f, -19.f));
    }

    else if(shipDesign == ShipType::boss)
    {
        m_shipShape.setPointCount(4);
        m_shipShape.setPoint(0, sf::Vector2f( 25.f,   0.f));
        m_shipShape.setPoint(1, sf::Vector2f(- 30.f,  25.f));
        m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
        m_shipShape.setPoint(3, sf::Vector2f(- 30.f, -25.f));
    }

    m_shipShape.setPosition(spawnPos);
    m_shipShape.setFillColor(sf::Color::Transparent);
    m_shipShape.setOutlineThickness(1); //old 0.75
    m_shipShape.setOutlineColor(aColor);

    //fill zero
    m_lastFireTime = 0;
    m_lastFullTime = 0;

    m_Point = point;
    m_fireDelay = fireDelay;
    m_shipType = shipDesign;

    m_lastFullTime = 2;
    std::cout << "EnnemyShip::EnnemyShip()" << std::endl;
}

sf::ConvexShape EnnemyShip::getConvexShape()
{
    return m_shipShape;
}

void EnnemyShip::move(sf::Vector2f aPosition)
{
    float angle = (float) atan2(m_shipShape.getPosition().y - aPosition.y, m_shipShape.getPosition().x - aPosition.x);
    m_shipShape.setRotation((float) (angle * (180/M_PI)) + 180); // + 180 because u want to point the right point

    m_shipShape.move(cosf((float) (m_shipShape.getRotation()*M_PI/180.f))*m_moveSpeed * 1,
                     sinf((float) (m_shipShape.getRotation()*M_PI/180.f))*m_moveSpeed * 1);
}

EnnemyShip::~EnnemyShip()
{
    //m_projectile.erase(m_projectile.begin() + m_projectile.size());
    std::cout << "EnnemyShip::~EnnemyShip()" << std::endl;
}

Projectile* EnnemyShip::fire()
{
    return new Projectile(m_shipShape.getPosition(), m_shipShape.getRotation(), sf::Color::Red, m_projectileSpeed);
}

void EnnemyShip::setLastFireTime(float lastFireTime)
{
    m_lastFireTime = lastFireTime;
}

void EnnemyShip::setLastFullTime(float lastFullTime)
{
    m_lastFullTime = lastFullTime;
}

float EnnemyShip::getLastFireTime()
{
    return m_lastFireTime;
}

float EnnemyShip::getLastFullTime()
{
    return m_lastFullTime;
}

int EnnemyShip::scoreToGet()
{
    return m_Point;
}

int EnnemyShip::getFireDelay()
{
    return m_fireDelay;
}

void EnnemyShip::setLifeCount(short lifeCount)
{
    m_life = lifeCount;
}

short EnnemyShip::getLifeCount()
{
    return m_life;
}

int EnnemyShip::getDropRate()
{
    return m_dropRate;
}

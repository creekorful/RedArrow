#ifndef SPACEINVADERS_ENNEMYSHIP_H
#define SPACEINVADERS_ENNEMYSHIP_H
#include "Ship.h"
#include "Projectile.h"
#include <math.h>

enum ShipType : int
{
    arrowShip = 1,
    speedSpeederShip = 2,
    fireSpeedShip = 3,
    sniperShip = 4,
    ultraSpeed = 5,
    boss = 6
};

class EnnemyShip : public Ship
{
public:
    EnnemyShip(sf::Vector2f spawnPos, float vitesse, sf::Color aColor, int point, int fireDelay, int design, float projectileSpeed, short lifeCount, int dropRate);
    sf::ConvexShape getConvexShape();
    void move(sf::Vector2f aPosition);
    Projectile* fire();
    void setLastFireTime(float lastFireTime);
    void setLastFullTime(float lastFullTime);
    float getLastFireTime();
    float getLastFullTime();
    int scoreToGet();
    int getDropRate();
    int getFireDelay();
    short getLifeCount();
    void setLifeCount(short lifeCount);
    ~EnnemyShip();

private:
    std::vector<Projectile*> m_projectile;
    sf::ConvexShape m_shipShape;
    float m_rotSpeed;
    float m_moveSpeed;
    float m_lastFireTime;
    float m_lastFullTime;
    int m_dropRate;
    int m_Point;
    int m_fireDelay;
    int m_shipType;
    short m_life;
    float m_projectileSpeed;

};


#endif //SPACEINVADERS_ENNEMYSHIP_H

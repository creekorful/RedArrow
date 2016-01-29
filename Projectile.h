//
// Created by creekorful on 21/09/2015.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/ConvexShape.hpp>

class Projectile
{
public:
    Projectile(sf::Vector2f originalPos, float angle, sf::Color aColor, float projectileSpeed);
    void move(float angle);
    sf::ConvexShape getProjectileShape();
    ~Projectile();

private:
    sf::ConvexShape m_projectileShape;
    float m_projectileSpeed;
    float m_angle;
};


#endif //SPACEINVADERS_PROJECTILE_H

//
// Created by creekorful on 21/09/2015.
//

#include <iostream>
#include "Projectile.h"
#include "Ship.h"

Projectile::Projectile(sf::Vector2f originalPos, float angle, sf::Color aColor, float projectileSpeed)
{
    m_projectileShape.setPointCount(4);
    m_projectileShape.setPoint(0, sf::Vector2f(00.f, 0.f));
    m_projectileShape.setPoint(1, sf::Vector2f(20.f, 0.f));
    m_projectileShape.setPoint(2, sf::Vector2f(20.f, 1.f));
    m_projectileShape.setPoint(3, sf::Vector2f(00.f, 1.f));
    m_projectileShape.setPosition(originalPos);
    m_projectileShape.setFillColor(aColor);
    m_angle = angle;
    m_projectileSpeed = projectileSpeed;
}

void Projectile::move(float delta)
{
    m_projectileShape.setRotation(m_angle);
    m_projectileShape.move( cosf((float) (m_angle*M_PI/180.f)) * m_projectileSpeed * delta,
                            sinf((float) (m_angle*M_PI/180.f)) * m_projectileSpeed * delta);
}

sf::ConvexShape Projectile::getProjectileShape()
{
    return m_projectileShape;
}

Projectile::~Projectile()
{

}

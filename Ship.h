//
// Created by creekorful on 21/09/2015.
//

#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#define M_PI		3.14159265358979323846


class Ship //classe abstraite
{
public:
    Ship();
    virtual sf::ConvexShape getConvexShape() = 0;
    virtual ~Ship();
};


#endif //SPACEINVADERS_SHIP_H

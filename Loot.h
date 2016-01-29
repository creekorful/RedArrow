//
// Created by creekorful on 29/09/2015.
//

#ifndef REDARROW_LOOT_H
#define REDARROW_LOOT_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

class Loot
{
public:
    enum LootType : int
    {
        Health1 = 1,
        Health2 = 2,
        MoreMoveSpeed = 3,
        MoreFireSpeed = 4
    };

    Loot(sf::Vector2f spawnPos, int aLootType);
    bool isUnder(sf::Vector2f shipPos);
    int getLootType();
    sf::ConvexShape* getConvexShape();

private:
    int m_lootType;
    sf::Vector2f m_pos;
    sf::ConvexShape* m_convexShape;

};


#endif //REDARROW_LOOT_H

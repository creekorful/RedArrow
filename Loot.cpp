#include "Loot.h"

Loot::Loot(sf::Vector2f spawnPos, int aLootType)
{
    m_pos = spawnPos;
    m_lootType = aLootType;

    m_convexShape = new sf::ConvexShape();

    if(aLootType == Loot::Health1)
    {
        m_convexShape->setPointCount(12);
        m_convexShape->setOutlineThickness(1);
        m_convexShape->setFillColor(sf::Color::Transparent);
        m_convexShape->setOutlineColor(sf::Color::Green);
        m_convexShape->setPoint(0, sf::Vector2f(3, 3));
        m_convexShape->setPoint(1, sf::Vector2f(6, 3));

        m_convexShape->setPoint(2, sf::Vector2f(6, 6));
        m_convexShape->setPoint(3, sf::Vector2f(9, 6)); //X, Y

        m_convexShape->setPoint(4, sf::Vector2f(9, 9));
        m_convexShape->setPoint(5, sf::Vector2f(6, 9));

        m_convexShape->setPoint(6, sf::Vector2f(6, 12));
        m_convexShape->setPoint(7, sf::Vector2f(3, 12));

        m_convexShape->setPoint(8, sf::Vector2f(3, 9));
        m_convexShape->setPoint(9, sf::Vector2f(0, 9));

        m_convexShape->setPoint(10, sf::Vector2f(0, 6));
        m_convexShape->setPoint(11, sf::Vector2f(3, 6));

        m_convexShape->setScale(sf::Vector2f(2,2));
    }

    else if(aLootType == Loot::Health2)
    {
        m_convexShape->setPointCount(12);
        m_convexShape->setOutlineThickness(1);
        m_convexShape->setFillColor(sf::Color::Transparent);
        m_convexShape->setOutlineColor(sf::Color(255,215,0));
        m_convexShape->setPoint(0, sf::Vector2f(3, 3));
        m_convexShape->setPoint(1, sf::Vector2f(6, 3));

        m_convexShape->setPoint(2, sf::Vector2f(6, 6));
        m_convexShape->setPoint(3, sf::Vector2f(9, 6)); //X, Y

        m_convexShape->setPoint(4, sf::Vector2f(9, 9));
        m_convexShape->setPoint(5, sf::Vector2f(6, 9));

        m_convexShape->setPoint(6, sf::Vector2f(6, 12));
        m_convexShape->setPoint(7, sf::Vector2f(3, 12));

        m_convexShape->setPoint(8, sf::Vector2f(3, 9));
        m_convexShape->setPoint(9, sf::Vector2f(0, 9));

        m_convexShape->setPoint(10, sf::Vector2f(0, 6));
        m_convexShape->setPoint(11, sf::Vector2f(3, 6));

        m_convexShape->setScale(sf::Vector2f(2,2));
    }

    else if(aLootType == Loot::MoreMoveSpeed)
    {
        m_convexShape->setPointCount(7);
        m_convexShape->setOutlineThickness(0.75); //todo better arrow
        m_convexShape->setFillColor(sf::Color::Transparent);
        m_convexShape->setOutlineColor(sf::Color::Blue);

        m_convexShape->setPoint(0, sf::Vector2f(10, 9));
        m_convexShape->setPoint(1, sf::Vector2f(15, 8));

        m_convexShape->setPoint(2, sf::Vector2f(15, 9));
        m_convexShape->setPoint(3, sf::Vector2f(20, 9)); //X, Y

        m_convexShape->setPoint(4, sf::Vector2f(20, 10));
        m_convexShape->setPoint(5, sf::Vector2f(15, 10));
        m_convexShape->setPoint(6, sf::Vector2f(15, 11));

        m_convexShape->setScale(sf::Vector2f(3,3));
    }

    else if(aLootType == Loot::MoreFireSpeed) //todo design loot
    {
        m_convexShape->setPointCount(4);
        m_convexShape->setPoint(0, sf::Vector2f(00.f, 0.f));
        m_convexShape->setPoint(1, sf::Vector2f(20.f, 0.f));
        m_convexShape->setPoint(2, sf::Vector2f(20.f, 1.f));
        m_convexShape->setPoint(3, sf::Vector2f(00.f, 1.f));
        m_convexShape->setFillColor(sf::Color::Yellow);
    }

    m_convexShape->setPosition(spawnPos);
}

bool Loot::isUnder(sf::Vector2f shipPos)
{
    return sqrt(pow(m_pos.x - shipPos.x, 2) + pow(m_pos.y - shipPos.y, 2)) < 25;
}

int Loot::getLootType()
{
    return m_lootType;
}

sf::ConvexShape* Loot::getConvexShape()
{
    return m_convexShape;
}

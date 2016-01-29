#include "PlayerShip.h"
#include "Loot.h"

PlayerShip::PlayerShip(short life) : Ship()
{
    m_rotSpeed = 0.50f; //todo default rot speed 0.25f
    m_moveSpeed = 0.0;

    m_moveStep = 0.100;
    m_maxMoveSpeed = 0.600;

    m_fireDelay = 450;

    m_playerLife = life;

    m_shipShape.setPointCount(4);
    m_shipShape.setPoint(0, sf::Vector2f( 12.f,   0.f));
    m_shipShape.setPoint(1, sf::Vector2f(- 6.f,  11.f));
    m_shipShape.setPoint(2, sf::Vector2f(  0.f,   0.f));
    m_shipShape.setPoint(3, sf::Vector2f(- 6.f, -11.f));
    m_shipShape.setPosition(50, 50);
    m_shipShape.setFillColor(sf::Color::Transparent);
    m_shipShape.setOutlineThickness(0.75);
    m_shipShape.setOutlineColor(sf::Color::Red);

    //Set up fire song
    m_fireSoundBuffer.loadFromFile("audio/fire_song.ogg");
    m_fireSound.setBuffer(m_fireSoundBuffer);

    m_isSuperFireEnabled = false;

    m_lastDelay = sf::seconds(0);
    m_fireDelay = 450;
    m_fireCount = 0;
    std::cout << "PlayerShip::PlayerShip()" << std::endl;
    return;
}

PlayerShip::~PlayerShip()
{
    std::cout << "PlayerShip::~PlayerShip()" << std::endl;
    return;
}

void PlayerShip::manangeEvent(int delta, int xLen, int yLen, sf::Time elapsedTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_shipShape.rotate(-m_rotSpeed * delta);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_shipShape.rotate( m_rotSpeed * delta);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        if(m_moveSpeed < m_maxMoveSpeed) //todo Speed acc max default 0.600
            m_moveSpeed += m_moveStep; //speed acc todo default : 0.0005
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(m_moveSpeed > -m_maxMoveSpeed) //todo Speed acc neg min default -0.25
            m_moveSpeed -= m_moveStep; //speed acc todo default : 0.0005
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (elapsedTime - m_lastDelay >= sf::milliseconds(m_fireDelay))) //fire (disable m_lastDelay inspection for superpower) or change m_lastdelay value check (450ms is good)
    {
        m_shipProjectiles.push_back(new Projectile(m_shipShape.getPosition(), m_shipShape.getRotation(), sf::Color::Green, 0.50f));
        m_fireSound.play();
        m_lastDelay = elapsedTime; //update counter
        m_fireCount++;
    }

    //check for superpower
    if(elapsedTime - m_superFireLaunchTime >= sf::seconds(10) && m_isSuperFireEnabled)
    {
        m_fireDelay = 450;
        m_isSuperFireEnabled = false;
    }
    if(elapsedTime - m_superSpeedLaunchTime >= sf::seconds(10) && m_isSuperSpeedEnabled)
    {
        m_moveStep = 0.100;
        m_maxMoveSpeed = 0.600;
        m_moveSpeed = 0.600; //reset inertie
        m_isSuperSpeedEnabled = false;
    }


    //then move
    m_shipShape.move(cosf((float) (m_shipShape.getRotation()*M_PI/180.f))*m_moveSpeed * delta,
                     sinf((float) (m_shipShape.getRotation()*M_PI/180.f))*m_moveSpeed * delta);

    //système anti dépassement
    if(m_shipShape.getPosition().y <= 0)
        m_shipShape.setPosition(sf::Vector2f(m_shipShape.getPosition().x, yLen));
    if(m_shipShape.getPosition().y > yLen)
        m_shipShape.setPosition(sf::Vector2f(m_shipShape.getPosition().x, 0));
    if(m_shipShape.getPosition().x <= 0)
        m_shipShape.setPosition(sf::Vector2f(xLen, m_shipShape.getPosition().y));
    if(m_shipShape.getPosition().x > xLen)
        m_shipShape.setPosition(sf::Vector2f(0, m_shipShape.getPosition().y));

    //système anti dépassement (pour proj)
    for(int iCurrentProj = 0; iCurrentProj < m_shipProjectiles.size(); iCurrentProj++)
    {
        if(m_shipProjectiles[iCurrentProj] != nullptr)
        {
            if(m_shipProjectiles[iCurrentProj]->getProjectileShape().getPosition().y <= 0)
                m_shipProjectiles[iCurrentProj] = nullptr;
            else if(m_shipProjectiles[iCurrentProj]->getProjectileShape().getPosition().y > yLen)
                m_shipProjectiles[iCurrentProj] = nullptr;
            else if(m_shipProjectiles[iCurrentProj]->getProjectileShape().getPosition().x <= 0)
                m_shipProjectiles[iCurrentProj] = nullptr;
            else if(m_shipProjectiles[iCurrentProj]->getProjectileShape().getPosition().x > xLen) //m_shipProjectiles.erase(m_shipProjectiles.begin() + iCurrentProj);
                m_shipProjectiles[iCurrentProj] = nullptr;
        }
    }
}

sf::ConvexShape PlayerShip::getConvexShape()
{
    return m_shipShape;
}

void PlayerShip::draw(sf::RenderWindow* window)
{
    window->draw(m_shipShape);

    for(int iCurrentProjectile = 0; iCurrentProjectile < m_shipProjectiles.size(); iCurrentProjectile++)
    {
        if(m_shipProjectiles[iCurrentProjectile] != nullptr)
        {
            m_shipProjectiles[iCurrentProjectile]->move(19*m_maxMoveSpeed); //todo ship speed for player bullet default 8 (19*m_moveSpeed for speed ctrl bug)
            window->draw(m_shipProjectiles[iCurrentProjectile]->getProjectileShape());
        }
    }
}

std::vector<Projectile *> PlayerShip::getShipProjectiles()
{
    return m_shipProjectiles;
}

void PlayerShip::setPlayerProjectiles(std::vector<Projectile *> projectiles)
{
    m_shipProjectiles = projectiles;
}

sf::Int32 PlayerShip::getFireCount()
{
    return m_fireCount;
}

void PlayerShip::applyLoot(int lootType, sf::Time currentTime)
{
    if(lootType == Loot::Health1)
        m_playerLife += 3;
    else if(lootType == Loot::Health2)
        m_playerLife += 5;
    else if(lootType == Loot::MoreMoveSpeed)
    {
        m_maxMoveSpeed = 1.200;
        m_moveSpeed = 0.400;
        m_superSpeedLaunchTime = currentTime;
        m_isSuperSpeedEnabled = true;
    }
    else if(lootType == Loot::MoreFireSpeed)
    {
        m_fireDelay = 100;
        m_superFireLaunchTime = currentTime;
        m_isSuperFireEnabled = true;
    }
}

void PlayerShip::setPlayerLife(short playe)
{
    m_playerLife = playe;
}

short PlayerShip::getPlayerLife()
{
    return m_playerLife;
}

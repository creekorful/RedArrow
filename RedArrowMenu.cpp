#include <iostream>
#include "RedArrowMenu.h"
#include "PlayerShip.h"
#include "RedArrowSinglePlayer.h"
#include "RedArrowMultiPlayer.h"

RedArrowMenu::RedArrowMenu(sf::RenderWindow* window)
{
    std::cout << "RedArrowMenu::RedArrowMenu()" << std::endl;

    //Here build choose menu
    PlayerShip playerShip(10);
    sf::Text singlePlayerText;
    sf::Text multiplayerText;
    sf::Text exitText;
    sf::RectangleShape singlePlayerRect;
    sf::FloatRect* singlePlayerSolid;
    sf::RectangleShape multiPlayerRect;
    sf::FloatRect* multiPlayerSolid;
    sf::RectangleShape exitShape;
    sf::FloatRect* exitSolid;

    sf::Clock clock;

    sf::Font defaultFont;
    defaultFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    singlePlayerText.setFont(defaultFont);
    singlePlayerText.setString("Singleplayer");
    singlePlayerText.setCharacterSize(25);
    singlePlayerText.setColor(sf::Color::Yellow);
    singlePlayerText.setPosition(sf::Vector2f(window->getSize().x/2, 100));
    singlePlayerRect.setPosition(sf::Vector2f(window->getSize().x/2-10, 100-10));
    singlePlayerRect.setSize(sf::Vector2f(170, 50));
    singlePlayerRect.setOutlineThickness(1);
    singlePlayerRect.setOutlineColor(sf::Color::Yellow);
    singlePlayerRect.setFillColor(sf::Color::Transparent);
    singlePlayerSolid = new sf::FloatRect(window->getSize().x/2-10, 100-10, 170, 50);

    multiplayerText.setFont(defaultFont);
    multiplayerText.setString("Multiplayer");
    multiplayerText.setCharacterSize(25);
    multiplayerText.setColor(sf::Color::Yellow);
    multiplayerText.setPosition(sf::Vector2f(100, window->getSize().y/2));
    multiPlayerRect.setPosition(sf::Vector2f(100-10, window->getSize().y/2-10));
    multiPlayerRect.setSize(sf::Vector2f(150, 60));
    multiPlayerRect.setOutlineThickness(1);
    multiPlayerRect.setOutlineColor(sf::Color::Yellow);
    multiPlayerRect.setFillColor(sf::Color::Transparent);
    multiPlayerSolid = new sf::FloatRect(100-10, window->getSize().y/2-10, 150, 60);

    exitText.setFont(defaultFont);
    exitText.setString("Exit");
    exitText.setCharacterSize(25);
    exitText.setColor(sf::Color::Yellow);
    exitText.setPosition(sf::Vector2f(window->getSize().x-150, window->getSize().y/2));
    exitShape.setPosition(window->getSize().x-150-10, (window->getSize().y/2)-10);
    exitShape.setSize(sf::Vector2f(80, 50));
    exitShape.setOutlineThickness(1);
    exitShape.setOutlineColor(sf::Color::Yellow);
    exitShape.setFillColor(sf::Color::Transparent);
    exitSolid = new sf::FloatRect(window->getSize().x-150-10, (window->getSize().y/2)-10, 80, 50);

    sf::Text info;
    info.setFont(defaultFont);
    info.setString("RedArrow 0.5 alpha build.\nShoot the selected option.");
    info.setCharacterSize(20);
    info.setPosition((window->getSize().x/2)-info.getString().getSize(), (window->getSize().y/2));
    info.setColor(sf::Color::Yellow);

    m_music.openFromFile("audio/main_menu_music.ogg");
    m_music.setLoop(true);
    m_music.play();

    while(window->isOpen())
    {
        //clock.restart();
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window->close();
        }

        window->clear(sf::Color::Black);
        playerShip.manangeEvent(5, window->getSize().x, window->getSize().y, clock.getElapsedTime()); //todo player speed
        playerShip.draw(window); //draw player ship and proj

        //Here draw text and other
        window->draw(singlePlayerText);
        window->draw(singlePlayerRect);
        window->draw(multiplayerText);
        window->draw(multiPlayerRect);
        window->draw(exitText);
        window->draw(exitShape);
        window->draw(info);

        window->display();


        //Here collision
        for(int iCurrentProjectile = 0; iCurrentProjectile < playerShip.getShipProjectiles().size(); iCurrentProjectile++)
        {
            if(playerShip.getShipProjectiles()[iCurrentProjectile] != nullptr) //if current projectile exist
            {
                sf::Vector2f currentShipProj = playerShip.getShipProjectiles()[iCurrentProjectile]->getProjectileShape().getPosition(); //Get current projectile proj

                if(singlePlayerSolid->contains(currentShipProj))
                {
                    this->~RedArrowMenu();
                    new RedArrowSinglePlayer(window);
                }
                else if(multiPlayerSolid->contains(currentShipProj))
                {
                    this->~RedArrowMenu();
                    new RedArrowMultiPlayer(window);
                }

                    //Close menu
                else if(exitSolid->contains(currentShipProj))
                {
                    this->~RedArrowMenu();
                    window->close();
                }
            }
        }
    }
}

RedArrowMenu::~RedArrowMenu()
{
    m_music.stop();
    std::cout << "RedArrowMenu::~RedArrowMenu()" << std::endl;
}

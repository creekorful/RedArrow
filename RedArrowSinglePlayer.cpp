#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include "RedArrowSinglePlayer.h"
#include "PlayerShip.h"
#include "EnnemyShip.h"
#include "RedArrowMenu.h"
#include "Loot.h"

RedArrowSinglePlayer::RedArrowSinglePlayer(sf::RenderWindow *window)
{
    std::cout << "RedArrowSinglePlayer::RedArrowSinglePlayer()" << std::endl;
    std::vector<EnnemyShip *> ennemis;
    std::vector<sf::CircleShape> stars; //beautiful background
    std::vector<Loot*> loots;
    PlayerShip playerShip(15); //10 life

    sf::Clock clock;
    sf::Clock fireClock;
    sf::Time frameTime;

    int scoreTotal = 0;
    int nombreDeKill = 0;
    int nombreDeToucher = 0; //For accuracy purposes
    int nombreEnnemiMax = 7;
    int nombreEnnemi = 0;
    //unsigned short playerLife = 10;
    int vagueActuelle = 0;
    bool isProjUnderPlayerShip = false;

    static float defaultProjectileSpeed = 0.50f;
    static float highProjectileSpeed = 2.f;

    sf::Font defaultFont;
    defaultFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    sf::Text score;
    score.setPosition(window->getSize().x-150, 20);
    score.setFont(defaultFont);
    score.setCharacterSize(15);

    sf::Text endMessage;
    endMessage.setPosition(window->getSize().x/2, window->getSize().y/2);
    endMessage.setFont(defaultFont);
    endMessage.setCharacterSize(20);
    endMessage.setColor(sf::Color::Yellow);

    //fire song for ennemi
    m_ennemiFireSongBuffer.loadFromFile("audio/ennemi_fire_song.ogg");
    m_ennemiFireSound.setBuffer(m_ennemiFireSongBuffer);

    //Explode song for ennemi
    m_ennemiExplodeBuffer.loadFromFile("audio/ennemi_explode.ogg");
    m_ennemiExplodeSound.setBuffer(m_ennemiExplodeBuffer);

    //loose life song
    m_looseLifeBuffer.loadFromFile("audio/lose_life_song.ogg");
    m_looseLifeSong.setBuffer(m_looseLifeBuffer);

    //got a loot song
    m_gotALootBuffer.loadFromFile("audio/got_a_loot.ogg");
    m_gotALootSong.setBuffer(m_gotALootBuffer);

    //ambient music
    m_ambientMusic.openFromFile("audio/singleplayer_ambient.ogg");
    m_ambientMusic.setLoop(true);
    m_ambientMusic.play();

    //win music
    m_winMusic.openFromFile("audio/you_win.ogg");
    m_winMusic.setLoop(true);

    std::vector<Projectile*> allProjectiles;

    //Here generate star
    for(int iCurrentStar = 0; iCurrentStar < 150; iCurrentStar++)
    {
        sf::CircleShape currentStarShape;
        currentStarShape.setFillColor(sf::Color::White);
        currentStarShape.setRadius(rand()%2);
        currentStarShape.setPosition(rand()%window->getSize().x, rand()%window->getSize().y);
        stars.push_back(currentStarShape);
    }

    while(window->isOpen())
    {
        sf::Event event;
        for(int iCurrentEnnemyShip = 0; iCurrentEnnemyShip < ennemis.size(); iCurrentEnnemyShip++)
            ennemis[iCurrentEnnemyShip]->setLastFullTime(ennemis[iCurrentEnnemyShip]->getLastFullTime() + frameTime.asSeconds());

        frameTime = clock.restart();

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                this->~RedArrowSinglePlayer();
                new RedArrowMenu(window);
            }

            //ennnemis (spawnX, spawnY, speed, color, scoreToGet, fireDelay, shipdesign, projectile speed, nombreDeVie, dropRate(percentage))
            if(nombreDeKill < 5 && nombreEnnemi < nombreEnnemiMax)
            {
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 0.50f, sf::Color::Yellow, 1, 5, ShipType::arrowShip, defaultProjectileSpeed, 0, 7)) ; //Standard ennemi (speed normal, fireSpeed normal)
                nombreEnnemi++;
                vagueActuelle = 1;
            }

            else if(nombreDeKill > 5 && nombreDeKill < 10 && nombreEnnemi < nombreEnnemiMax)
            {
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 1.8f, sf::Color::White, 2, 3, ShipType::speedSpeederShip, defaultProjectileSpeed, 0, 15)); //speed ennemi (speed high, fireSpeed normal)
                nombreEnnemi++;
                vagueActuelle = 2;
            }
            else if(nombreDeKill > 10 && nombreDeKill < 20 && nombreEnnemi < nombreEnnemiMax)
            {
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 0.50f, sf::Color::Blue, 3, 1, ShipType::fireSpeedShip, defaultProjectileSpeed, 1, 20)); //firespeed ennemi (speed normal, fireSpeed high)
                nombreEnnemi++;
                vagueActuelle = 3;
            }
            else if(nombreDeKill > 20 && nombreDeKill < 30 && nombreEnnemi < nombreEnnemiMax)
            {
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 0.50f, sf::Color::Green, 5, 7, ShipType::sniperShip, highProjectileSpeed, 1, 30)); //snipership ennemi (speed normal, fireSpeed low, projectile speed high)
                nombreEnnemi++;
                vagueActuelle = 4;
            }
            else if(nombreDeKill > 30 && nombreDeKill < 40 && nombreEnnemi < nombreEnnemiMax)
            {
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 2.f, sf::Color::Cyan, 10, 1, ShipType::ultraSpeed, defaultProjectileSpeed, 2, 45)); //firespeed ennemi (speed very high, fireSpeed high)
                nombreEnnemi++;
                vagueActuelle = 5;
            }
            else if(nombreDeKill > 0 && nombreDeKill < 50  && nombreEnnemi < 1)
            {
                //here spawn boss
                ennemis.push_back(new EnnemyShip(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y), 0.25f, sf::Color::Magenta, 10, 1, ShipType::boss, highProjectileSpeed, 4, 65)); //firespeed ennemi (speed very high, fireSpeed high)
                nombreEnnemi++;
                vagueActuelle = 6;
            }

            else if(nombreEnnemi == 0) //you kill everbody
            {
                std::ostringstream oss;
                float scoreFinal = (playerShip.getFireCount()/100)*scoreTotal;
                oss << "You win !\nScore final: " << scoreFinal; //Todo calculate true score total (and write to saves maybe)
                endMessage.setString(oss.str());
                m_ambientMusic.stop();
                m_winMusic.play();
            }

        }

        window->clear(sf::Color::Black); //window color

        //Draw background star
        for(int iCurrentStar=0;iCurrentStar<stars.size();iCurrentStar++)
            window->draw(stars[iCurrentStar]);

        playerShip.manangeEvent(6, window->getSize().x, window->getSize().y, fireClock.getElapsedTime()); //todo player speed default : 4 todo depend of windows size
        playerShip.draw(window); //draw player ship and proj


        //colision for ennemy
        std::vector<Projectile *> playerProjectile = playerShip.getShipProjectiles();
        for (int iCurrentProjectile = 0; iCurrentProjectile < playerProjectile.size(); iCurrentProjectile++)
        {
            for (int iCurrentEnnmiToTest = 0; iCurrentEnnmiToTest < ennemis.size(); iCurrentEnnmiToTest++)
            {
                if(playerProjectile[iCurrentProjectile] != nullptr) //is currentprojectile exist
                {
                    if (sqrt(pow(playerProjectile[iCurrentProjectile]->getProjectileShape().getPosition().x - ennemis[iCurrentEnnmiToTest]->getConvexShape().getPosition().x, 2) + pow(playerProjectile[iCurrentProjectile]->getProjectileShape().getPosition().y - ennemis[iCurrentEnnmiToTest]->getConvexShape().getPosition().y, 2)) < 35)
                    {
                        if (ennemis[iCurrentEnnmiToTest]->getLifeCount() != 0)
                        {
                            ennemis[iCurrentEnnmiToTest]->setLifeCount(ennemis[iCurrentEnnmiToTest]->getLifeCount() - (short) 1);
                            nombreDeToucher++;
                        }
                        else //if ennemi has no more life
                        {
                            scoreTotal += ennemis[iCurrentEnnmiToTest]->scoreToGet();
                            nombreEnnemi--;
                            nombreDeKill++;
                            nombreDeToucher++;
                            m_ennemiExplodeSound.play(); //play explosion sound

                            //Here manage loot
                            if(rand()%101 < ennemis[iCurrentEnnmiToTest]->getDropRate()) //drop date chance
                            {
                                loots.push_back(new Loot(ennemis[iCurrentEnnmiToTest]->getConvexShape().getPosition(), rand()%5+1));
                            }
                            ennemis.erase(ennemis.begin() + iCurrentEnnmiToTest);
                        }

                        playerProjectile[iCurrentProjectile] = nullptr;
                    }
                }

            }
        }
        playerShip.setPlayerProjectiles(playerProjectile);

        //Draw and manage ennemi
        for (int iCurrentEnnemi = 0; iCurrentEnnemi < ennemis.size(); iCurrentEnnemi++)
        {
            ennemis[iCurrentEnnemi]->move(playerShip.getConvexShape().getPosition()); //move all ennemy toward you

            if(ennemis[iCurrentEnnemi]->getLastFullTime() > ennemis[iCurrentEnnemi]->getLastFireTime() + ennemis[iCurrentEnnemi]->getFireDelay()) //ennemi fire
            {
                allProjectiles.push_back(ennemis[iCurrentEnnemi]->fire()); //add current ennmi proj to allprojectiles array
                m_ennemiFireSound.play();
                ennemis[iCurrentEnnemi]->setLastFireTime(ennemis[iCurrentEnnemi]->getLastFullTime());
            }
        }

        for(int iCurrentProjectile = 0; iCurrentProjectile < allProjectiles.size(); iCurrentProjectile++) //Draw all projectiles
        {
            //check collision for player
            if(allProjectiles[iCurrentProjectile] != nullptr) //todo remove this and try to remove projectile instead
            {
                if(sqrt(pow(allProjectiles[iCurrentProjectile]->getProjectileShape().getPosition().x - playerShip.getConvexShape().getPosition().x, 2) + pow(allProjectiles[iCurrentProjectile]->getProjectileShape().getPosition().y - playerShip.getConvexShape().getPosition().y, 2)) < 35 && !isProjUnderPlayerShip)
                {
                    playerShip.setPlayerLife((short) (playerShip.getPlayerLife()-1));
                    isProjUnderPlayerShip = true;
                    allProjectiles[iCurrentProjectile] = nullptr;
                    m_looseLifeSong.play(); //play lose life song

                    if (playerShip.getPlayerLife() == 0)
                    {
                        this->~RedArrowSinglePlayer();
                        endMessage.setColor(sf::Color::Red);
                        endMessage.setString("You failed.");
                        playerShip.~PlayerShip();
                        new RedArrowMenu(window);
                    }
                }
                else
                    isProjUnderPlayerShip = false;

                if(allProjectiles[iCurrentProjectile] != nullptr)
                {
                    allProjectiles[iCurrentProjectile]->move(0.50f * 9); //todo you can reduce time if user got slow mode loot def:9
                    window->draw(allProjectiles[iCurrentProjectile]->getProjectileShape());
                }
            }
        }

        for(int iCurrentEnnemi=0;iCurrentEnnemi<ennemis.size();iCurrentEnnemi++) //Draw all ennemis
            window->draw(ennemis[iCurrentEnnemi]->getConvexShape());

        for(int iCurrentLoot=0;iCurrentLoot<loots.size();iCurrentLoot++)
        {
            if(loots[iCurrentLoot] != nullptr)
            {
                window->draw(*loots[iCurrentLoot]->getConvexShape());

                if(loots[iCurrentLoot]->isUnder(playerShip.getConvexShape().getPosition()))
                {
                    playerShip.applyLoot(loots[iCurrentLoot]->getLootType(), fireClock.getElapsedTime());
                    m_gotALootSong.play();
                    loots[iCurrentLoot] = nullptr;
                }
            }
        }

        //Score
        std::ostringstream oss;
        oss.precision(2);
        oss << "Score: " << scoreTotal << "\nNombre de kill: " << nombreDeKill << "\nNombre de tir: " << playerShip.getFireCount();
        if(playerShip.getFireCount() > 0)
            oss << "\nPrécision: " << (nombreDeToucher*100)/playerShip.getFireCount() << "%\n";
        else
            oss << "\nPrécision: 0%\n";

        oss << "Nombre de vie: " << playerShip.getPlayerLife() << "\nNombre d'ennemi: " << nombreEnnemi << "/" << nombreEnnemiMax << "\nVague: " << vagueActuelle << "/6";
        score.setString(oss.str());
        window->draw(score);
        window->draw(endMessage);

        window->display();
    }

}

RedArrowSinglePlayer::~RedArrowSinglePlayer()
{
    m_ambientMusic.stop();
    m_winMusic.stop();
    std::cout << "RedArrowSinglePlayer::~RedArrowSinglePlayer()"<< std::endl;
}

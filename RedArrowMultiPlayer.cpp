#include <iostream>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include "RedArrowMultiPlayer.h"
#include "RedArrowMenu.h"

//todo timeout all receive and send func

RedArrowMultiPlayer::RedArrowMultiPlayer(sf::RenderWindow *window)
{
    sf::ConvexShape playerShip; //my ship
    playerShip.setPointCount(4);
    playerShip.setPoint(0, sf::Vector2f( 12.f,   0.f));
    playerShip.setPoint(1, sf::Vector2f(- 6.f,  11.f));
    playerShip.setPoint(2, sf::Vector2f(  0.f,   0.f));
    playerShip.setPoint(3, sf::Vector2f(- 6.f, -11.f));
    playerShip.setPosition(50, 50);
    playerShip.setFillColor(sf::Color::Transparent);
    playerShip.setOutlineThickness(0.75);
    playerShip.setOutlineColor(sf::Color::Red);

    FirstTrame firstTrame;
    std::cout << "RedArrowMultiPlayer::RedArrowMultiPlayer()" << std::endl;

    if(m_tcpSocket.connect(sf::IpAddress::LocalHost, 4242, sf::seconds(5)) != sf::Socket::Done)
    {
        std::cout << "RedArrowMultiPlayer::RedArrowMultiPlayer() : Unable to connect to server..." << std::endl;
        this->~RedArrowMultiPlayer();
        new RedArrowMenu(window);
    }

    std::cout << "Connection succefully ! Local port: " << m_tcpSocket.getLocalPort() << " remote port: " << m_tcpSocket.getRemotePort() << std::endl;
    m_ambientMusic.openFromFile("audio/multiplayer_ambient.ogg"); //launch ambient music
    m_ambientMusic.play();
    sf::Packet initTrame;

    while(m_tcpSocket.receive(initTrame) != sf::TcpSocket::Done);

    if(!(initTrame >> firstTrame.windowSizeX >> firstTrame.windowSizeY >> firstTrame.spawnPosX >> firstTrame.spawnPosY >> firstTrame.angle >> firstTrame.rotateSpeed)) //unpack init trame
    {
        std::cout << "unable to extract init packet... Exiting" << std::endl;
        this->~RedArrowMultiPlayer();
        new RedArrowMenu(window);
    }

    std::cout << "Init trame: " << std::endl;
    std::cout << "Window size x: " << firstTrame.windowSizeX << " y: " << firstTrame.windowSizeY << std::endl;
    std::cout << "Spawn pos x: " << firstTrame.spawnPosX << " y: " << firstTrame.spawnPosY << std::endl;
    std::cout << "Angle: " << firstTrame.angle << std::endl;
    std::cout << "Rotation speed: " << firstTrame.rotateSpeed << std::endl;
    std::cout << "Ship color is: " << firstTrame.shipColor << std::endl;
    playerShip.setPosition(sf::Vector2f(firstTrame.spawnPosX, firstTrame.spawnPosY));

    m_rotSpeed = firstTrame.rotateSpeed; //default 0.50f
    //playerShip.setOutlineColor(sf::Color(firstTrame.shipColor));


    while(window->isOpen())
    {
        window->clear(sf::Color::Black);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            playerShip.rotate(-m_rotSpeed * 6);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            playerShip.rotate( m_rotSpeed * 6);

        //first send rotation angle to server
        std::cout << "Send rotationTrame to server (" << playerShip.getRotation() << ")" << std::endl;
        sf::Packet rotationTrame;
        rotationTrame << playerShip.getRotation();
        if(m_tcpSocket.send(rotationTrame) == sf::Socket::Error) //send rotation trame to server
            std::cout << "Error occured when sending rotationTrame to server" << std::endl;

        //Here read response
        sf::Packet serverMoveResponse;
        ServerMoveTrameResponse serverMoveTrameResponse;
        serverMoveTrameResponse.id = "";
        serverMoveTrameResponse.newX = 0;
        serverMoveTrameResponse.newY = 0;

        if(m_tcpSocket.receive(serverMoveResponse) == sf::TcpSocket::Disconnected)
        {
            std::cout << "Error when reading response... Exiting." << std::endl;
            this->~RedArrowMultiPlayer();
            new RedArrowMenu(window);
        }
        else //packet received
        {
            if(serverMoveResponse >> serverMoveTrameResponse.id >> serverMoveTrameResponse.newX >> serverMoveTrameResponse.newY) //try to extract packet
                std::cout << "ServerMoveTrameResponse packet extracted succefully" << std::endl;
            else
                std::cout << "Unable to extract packet..." << std::endl;

            if(serverMoveTrameResponse.id == "mv") //if we received a move trame
            {
                std::cout << "My new position is x: " << serverMoveTrameResponse.newX << " y: " << serverMoveTrameResponse.newY << std::endl;
                playerShip.setPosition(serverMoveTrameResponse.newX, serverMoveTrameResponse.newY); //set player position calculated by server
            }

            //Here read clientcount and each client packet, then draw it

            window->draw(playerShip);
            window->display();
        }
    }
}

RedArrowMultiPlayer::~RedArrowMultiPlayer()
{
    m_ambientMusic.stop();
    std::cout << "RedArrowMultiPlayer::~RedArrowMultiPlayer" << std::endl;
}

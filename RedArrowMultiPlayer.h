#ifndef SPACEINVADERSMULTIPLAYER_H
#define SPACEINVADERSMULTIPLAYER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Audio/Music.hpp>

struct FirstTrame //trame sended by server the first time
{
    int windowSizeX; //game window size x
    int windowSizeY; //game window size y
    float spawnPosX; //spawn position x of the ship
    float spawnPosY; //Spawn position y of the ship
    float angle; //spawn rotation angle of the ship
    float rotateSpeed; //ship rotation speed
    sf::Uint32 shipColor;
};

struct ServerMoveTrameResponse //trame sended by the server to update client position
{
    //char id[2]; //trame id (should be mv)
    std::string id;
    float newX; //new position x of the ship
    float newY; //new position y of the ship
};

struct ClientMoveQuery //trame sended by client
{
    float angle;
};

struct ClientCount //sended by server (the client get the total number of client, so the number of Client packet to get)
{
    sf::Uint8 playerCount;
};

struct Client
{
    std::string id; //trame id (should be cli)
    float posX;
    float posY;
    float angle;
    sf::Uint32 shipColor;
};

class RedArrowMultiPlayer
{
public:
    RedArrowMultiPlayer(sf::RenderWindow* window);
    ~RedArrowMultiPlayer();

private:
    sf::TcpSocket m_tcpSocket;
    std::vector<Client> m_OtherPlayers; //used to get other player pos
    float m_rotSpeed;
    sf::Music m_ambientMusic;
};


#endif //SPACEINVADERSMULTIPLAYER_H

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "RedArrowMenu.h"

using namespace std;


///* before beta version *
//todo speed and rot and other fucking things will be calculted using windows size : HIGH
//todo multiplayer working server system : NORMAL
//todo config file for keyboard input and window size, fullscreen (search for json lib c++): LOW
//todo efficient checksum for multiplayer packet : NORMAL
//Todo remove ennemy proj when they are outside the screen : HIGH
//todo update speed and other using fps (with clock) : HIGH
//todo patch openAcl error : HIGH
//todo add realistic speed vector system : NORMAL
//todo projectile pass trough the screen and dissapear after a timeout : NORMAL

// in progress ...
//todo folder (source code organisation) : LOW
//todo better code organisation : HIGH (dont use user MVC pattern)


int main(int argc, char* argv[])
{
    const int x = 1920;
    const int y = 1080;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(x, y), "RedArrow 0.5", sf::Style::Fullscreen);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false); //hide mouse cursor
    new RedArrowMenu(window);
    return 0;
}
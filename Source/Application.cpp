#include "Application.h"

Application::Application(int argc, char** argv) : m_gameEngine(sf::VideoMode(800, 600), "RedArrow")
{

}

int Application::execute()
{
    while (m_gameEngine.isRunning())
    {
        m_gameEngine.execute();
    }

    return 0;
}

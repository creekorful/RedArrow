#include "Application.h"

Application::Application(int argc, char** argv)
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

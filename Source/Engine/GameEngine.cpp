#include "GameEngine.h"

GameEngine::GameEngine(sf::VideoMode mode, const std::string& title) : m_window(mode, title)
{
    m_stateManager.initialize();

    // configure window
    m_window.setFramerateLimit(60);
}

GameEngine::~GameEngine()
{
    m_stateManager.cleanup();
}

bool GameEngine::isRunning()
{
    return m_window.isOpen();
}

void GameEngine::execute()
{
    sf::Event event{};

    sf::Clock deltaClock;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            m_window.close();
        }

        m_stateManager.handleEvents(event);

        // Compute delta time
        sf::Time dt = deltaClock.restart();

        // clear window
        m_window.clear(sf::Color::Black);
        // Update physics
        m_stateManager.update(dt.asMilliseconds());
        // Draw current state
        m_stateManager.draw(m_window);
    }
}

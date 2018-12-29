#ifndef REDARROW_MAINMENUSTATE_H
#define REDARROW_MAINMENUSTATE_H


#include "../../Engine/GameState.h"

class MainMenuState : public GameState
{
public:
    void initialize() override;

    void cleanup() override;

    std::string title() const override;

    void handleEvents(const sf::Event& event) override;

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    static MainMenuState &instance()
    {
        static MainMenuState instance;
        return instance;
    }
};


#endif //REDARROW_MAINMENUSTATE_H

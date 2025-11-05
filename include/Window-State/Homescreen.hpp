#include "Game.hpp"
#include "UI/Button.hpp"
#include "UI/RoundRectShape.hpp"

class Homescreen{
private:
    Button playButton;
    Button resumeButton;
    Button settingButton;
    Button exitButton;

    sf::Text         Gamename;
    sf::RenderWindow &window;

public:

    Homescreen(sf::Font &font, sf::RenderWindow &window);

    Game::windowState nextState = Game::windowState::Homescreen;
    void UpdateGamenamePosition();
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void drawButton();
    void drawGamename();
    void run();
};
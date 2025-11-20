#include "Game.hpp"
#include "UI/Button.hpp"
#include "UI/RoundRectShape.hpp"

class Homescreen{
private:
    Button playButton;
    Button settingButton;
    Button exitButton;

    sf::Sprite BackgroundSprite;

    sf::Text         Gamename;
    sf::RenderWindow &window;

public:

    Homescreen(sf::Font &font, sf::RenderWindow &window, sf::Texture &BackgroundTexture);

    Game::windowState nextState = Game::windowState::Homescreen;
    void UpdateGamenamePosition();
    void setBackground(sf::Sprite &backgroundSprite);
    void updateButton(Mouse &mouse);
    void drawButton();
    void drawGamename();
    void run();
};
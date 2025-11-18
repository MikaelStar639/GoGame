#include <SFMl/Graphics.hpp>
#include "UI/Button.hpp"
#include "UI/Blur.hpp"
#include "Game-Play-Logic/GameState.hpp"
#include "Ultil.hpp"

class EndGameWindow{
private:
    sf::RectangleShape shape;
    Button replayButton, backButton;
    sf::Text text;
    Blur blur;
    float text_scale   = 0.5f;
    float text_align_v = 0.6f;
public:
    bool isClosed = false;
    bool isReset = false;

    void update(GameState &gameState);
    EndGameWindow(sf::Font &font);
    void run(sf::RenderWindow &window, Mouse &mouse);
};

#include <SFML/Graphics.hpp>

class Game{
private:
    enum class gameState{
        Homescreen,
        PlayOptions,
        Settings
    };

public:
    Game();

    gameState state;

    sf::RenderWindow window;
    void handleEvent();
    void run();
};
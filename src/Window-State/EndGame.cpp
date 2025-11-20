#include "Window-State/EndGame.hpp"

EndGameWindow::EndGameWindow(sf::Font &font) : 
    text(font), replayButton(font), backButton(font){
    
    //* Will update this later if have enough time

    //* shape:
    shape.setSize({800.f, 500.f});
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition({600.f, 450.f});
    shape.setFillColor(sf::Color(238, 238, 210));
    
    //* button:
    replayButton.setString("Replay");
    replayButton.setSize({300.f, 80.f});
    replayButton.setPosition({600.f, 500.f});

    backButton.setString("Back");
    backButton.setSize({300.f, 80.f});
    backButton.setPosition({600.f, 600.f});
}

void EndGameWindow::update(GameState &gameState){
    text.setFillColor(sf::Color::Black);
    if (gameState.blackScore > gameState.whiteScore){
        text.setString("Black Wins!!!");
    }
    else{
        text.setString("White Wins!!!");
    }
    text.setCharacterSize(50);
    text.setPosition({600.f, 350.f});
    alignText(text, 0.45f, text_align_v);
}

void EndGameWindow::run(sf::RenderWindow &window, Mouse &mouse){
    blur.draw(window);
    window.draw(shape);
    window.draw(text);
    replayButton.update(mouse);
    backButton.update(mouse);
    replayButton.draw(window);
    backButton.draw(window);

    if (backButton.onRelease){
        isClosed = true;
    }

    if (replayButton.onRelease){
        isReset = true;
    }
}
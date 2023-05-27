#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Window.h"

int main()
{
    /* Should be obtained from main menu */
	int gameboardWidth = 6;
	int gameboardHeight = 6;
    int playerCount = 1;

    // Init
	Gameboard gameBoard(gameboardWidth, gameboardHeight);
    Block gameBlockReference(0, 0, sf::Color::Blue);
    Block gameBlockReference2(0, 0, sf::Color::Red);

    // Add block to board
    gameBoard.addBlock(0, 0, &gameBlockReference);
    gameBoard.addBlock(0, 2, &gameBlockReference2);

	Window gameWindow(
        gameboardWidth * gameBlockReference.getWidth(), 
        gameboardHeight * gameBlockReference.getHeight(), "Concurrent Tetris");

	sf::Event event;

    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
        /* Main loop */
        gameWindow.clear();
        gameWindow.drawGameboard(&gameBoard, &gameBlockReference);
        gameWindow.drawScoreboard(69, 69);
        gameWindow.display();
    }

    return 0;
}
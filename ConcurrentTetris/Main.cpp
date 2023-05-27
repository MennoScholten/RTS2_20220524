#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Window.h"
#include <vector>
#include "Player.h"
#include "InputHandler.h"

int main()
{
    /* Should be obtained from main menu */
	int gameboardWidth = 20;
	int gameboardHeight = 20;
    int playerCount = 2;
    std::vector<Player*> players;
    
    Player player1(sf::Color::Blue, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    players.push_back(&player1);
    // Max 2 players for now
    if (playerCount >= 1) {
        Player player2(sf::Color::Blue, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
        players.push_back(&player2);
    }


    // Init
    InputHandler inputHandler;
	Gameboard gameBoard(gameboardWidth, gameboardHeight);
    Block gameBlockReference(0, 0, sf::Color::Blue);
    Block gameBlockReference2(0, 0, sf::Color::Red);

    // Add block to board
    gameBoard.addBlock(0, 0, &gameBlockReference);
    gameBoard.addBlock(0, 2, &gameBlockReference2);
	
    Tetromino* testTetro1 = new Tetromino(150.f, 150.f, Tetromino::blockType::Z);
    testTetro1->rotateTetromino(90.f);

    Tetromino* testTetro2 = new Tetromino(350.f, 150.f, Tetromino::blockType::L);
    testTetro2->rotateTetromino(90.f);

    Tetromino* testTetro3 = new Tetromino(450.f, 350.f, Tetromino::blockType::L);
    testTetro3->rotateTetromino(90.f);

    Tetromino* testTetro4 = new Tetromino(150.f, 450.f, Tetromino::blockType::I);
    testTetro4->rotateTetromino(90.f);

    // Add block to board
    gameBoard.addBlock(0, 0, &gameBlockReference);
    gameBoard.addBlock(0, 2, &gameBlockReference2);
    gameBoard.addTetromino(testTetro1);
    gameBoard.addTetromino(testTetro2);
    gameBoard.addTetromino(testTetro3);
    gameBoard.addTetromino(testTetro4);

	Window gameWindow(
        gameboardWidth * gameBlockReference.getWidth(), 
        gameboardHeight * gameBlockReference.getHeight(), "Concurrent Tetris");

	sf::Event event;

    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            inputHandler.processInput(players, event);
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

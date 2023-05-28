#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Window.h"
#include <vector>
#include "Player.h"
#include "InputHandler.h"
#include "Block.h"
#include "Tetromino.h"

int main()
{
    /* Should be obtained from main menu */
	int gameboardWidth = 22;
	int gameboardHeight = 22;
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

    
    Tetromino tetrominoI = tetrominoI.blockI(3, 3, sf::Color::Cyan, &gameBoard);
    player1.setActiveTetrimino(&tetrominoI);
    //Tetromino tetrominoL = tetrominoL.blockL(2, 2, sf::Color::White, &gameBoard);
    //player1.setActiveTetrimino(&tetrominoL);
    // Tetromino tetrominoJ = tetrominoJ.blockJ(2, 2, sf::Color::Blue, &gameBoard);
    // player1.setActiveTetrimino(&tetrominoJ);
    // Tetromino tetrominoZ = tetrominoZ.blockZ(2, 2, sf::Color::Green, &gameBoard);
    // player1.setActiveTetrimino(&tetrominoZ);
    // Tetromino tetrominoS = tetrominoS.blockS(2, 2, sf::Color::Red, &gameBoard);
    // player1.setActiveTetrimino(&tetrominoS);
    // Tetromino tetrominoT = tetrominoT.blockT(2, 2, sf::Color::Magenta, &gameBoard);
    // player1.setActiveTetrimino(&tetrominoT);
    // Tetromino tetrominoO = tetrominoO.blockO(2, 2, sf::Color::Yellow, &gameBoard);
    // player1.setActiveTetrimino(&tetrominoO);


	Window gameWindow(
        gameboardWidth * gameBlockReference.getWidth(), 
        gameboardHeight * gameBlockReference.getHeight(), "Concurrent Tetris");

	sf::Event event;

    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            inputHandler.processInput(players, &gameBoard, event);
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

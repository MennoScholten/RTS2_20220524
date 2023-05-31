#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Window.h"
#include <vector>
#include "Player.h"
#include "InputHandler.h"
#include "Block.h"
#include "Tetromino.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <random>


void gameLogicThread(std::vector<Player*> players, Gameboard* board, InputHandler* inputHandler, int gameBoardWidth)
{
    const int GAME_TICK_DURATION = 100;

    // Only singleplayer tested
    Tetromino tetrominoI = tetrominoI.blockI(2, 2, sf::Color::Cyan);
    Tetromino tetrominoT = tetrominoT.blockT(2, 2, sf::Color::Magenta);
    Tetromino tetrominoL = tetrominoL.blockL(2, 2, sf::Color::White);
    Tetromino tetrominoJ = tetrominoL.blockJ(2, 2, sf::Color::Blue);
    Tetromino tetrominoZ = tetrominoZ.blockZ(2, 2, sf::Color::Green);
    Tetromino tetrominoS = tetrominoS.blockS(2, 2, sf::Color::Red);
    Tetromino tetrominoO = tetrominoO.blockO(2, 2, sf::Color::Yellow);

    Tetromino* tetrominoListPlayer1[] = {&tetrominoI, &tetrominoT, &tetrominoL, &tetrominoJ, &tetrominoZ, &tetrominoS, &tetrominoO};

    // Only singleplayer tested
    Tetromino tetrominoI2 = tetrominoI2.blockI(18, 2, sf::Color::Cyan);
    Tetromino tetrominoT2 = tetrominoT2.blockT(18, 2, sf::Color::Magenta);
    Tetromino tetrominoL2 = tetrominoL2.blockL(18, 2, sf::Color::White);
    Tetromino tetrominoJ2 = tetrominoL2.blockJ(18, 2, sf::Color::Blue);
    Tetromino tetrominoZ2 = tetrominoZ2.blockZ(18, 2, sf::Color::Green);
    Tetromino tetrominoS2 = tetrominoS2.blockS(18, 2, sf::Color::Red);
    Tetromino tetrominoO2 = tetrominoO2.blockO(18, 2, sf::Color::Yellow);

    Tetromino* tetrominoListPlayer2[] = { &tetrominoI2, &tetrominoT2, &tetrominoL2, &tetrominoJ2, &tetrominoZ2, &tetrominoS2, &tetrominoO2};

    while (true) {
        // if player doesnt have an active block, spawn a block for player
        for (int i = 0; i < players.size(); i++) {
            if (i == 0) {
                if (players[i]->getActiveTetrimino() == nullptr) {
                    Tetromino* tetromino = tetrominoListPlayer1[std::rand() % 7];
                    tetromino->addToGameBoard(board);
                    players[i]->setActiveTetrimino(tetromino);
                }
            }

            else if(i==1) {
                if (players[i]->getActiveTetrimino() == nullptr) {
                    Tetromino* tetromino = tetrominoListPlayer2[std::rand() % 7];
                    tetromino->addToGameBoard(board);
                    players[i]->setActiveTetrimino(tetromino);
                }
            }
        }
        

        // Game tick move down
        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK_DURATION));

        // Move the active tetrimino down
        for (Player* player : players) {
            Tetromino* activeTetrimino = player->getActiveTetrimino();
            if (activeTetrimino != nullptr) {
                bool wasBlockMoved = activeTetrimino->moveDown(board);
                std::cout << "Move Down: " << wasBlockMoved << "\n";
                if (wasBlockMoved == false) {
                    player->setActiveTetrimino(nullptr);
                    // Freeze the block here
                }
            }
        }
        // Tetromino tetrominoI = tetrominoI.blockI(2, 2, sf::Color::Cyan, &gameBoard);
        // player1.setActiveTetrimino(&tetrominoI);
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
        // 
        // Here should be some sort of randomly suffled tetromino object queue
    }
}

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
    if (playerCount > 1) {
        Player player2(sf::Color::Blue, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
        players.push_back(&player2);
    }

    // Declare a mutex to protect the gameBoard
    std::mutex gameBoardMutex;

    // Init
    InputHandler inputHandler;
	Gameboard gameBoard(gameboardWidth, gameboardHeight);
    Block gameBlockReference(0, 0, sf::Color::Blue);  // This is only used to determine gameWindow size. Kind of weird.

	Window gameWindow(
        gameboardWidth * gameBlockReference.getWidth(), 
        gameboardHeight * gameBlockReference.getHeight(), "Concurrent Tetris");

	sf::Event event;

    // Start the logic thread
    std::thread gameThread(gameLogicThread, players, &gameBoard, &inputHandler, gameboardWidth);

    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            inputHandler.processInput(players, &gameBoard, event);
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
        /* Main loop */
        gameWindow.clear();
        // std::lock_guard<std::mutex> lock(gameBoardMutex);
        gameWindow.drawGameboard(&gameBoard, &gameBlockReference);
        gameWindow.drawScoreboard(69, 69);
        gameWindow.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include "include/Block.h"
#include "include/Gameboard.h"
#include "include/Window.h"
#include <vector>
#include "include/Player.h"
#include "include/InputHandler.h"
#include "include/Block.h"
#include "include/Tetromino.h"
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>


std::recursive_mutex gameboardMutex;
bool terminateThreads = false;

void gameLogicThread(std::vector<Player*> players, Gameboard* board, InputHandler* inputHandler)
{
    const int GAME_TICK_DURATION = 500;

    while (true) {
        if (terminateThreads == true) {
            return;
        }
        // if player doesnt have an active block, spawn a block for player
        for (Player* player : players) {
            if (player->getActiveTetrimino() == nullptr) {
                Tetromino* tetromino = new Tetromino();
                sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
                std::lock_guard<std::recursive_mutex> lock(gameboardMutex);
                tetromino->createRandomTetromino(0, board->getSizeY() / 2, color);
                std::lock_guard<std::recursive_mutex> lock2(gameboardMutex);
                bool gameOver = tetromino->addToGameBoard(board);
                if (!gameOver) {
                    std::cout << "Game Over!";
                    return;
                }
                player->setActiveTetrimino(tetromino);
            }
        }
        // Game tick move down
        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK_DURATION));

        // Move the active tetrimino down
        for (Player* player : players) {
            Tetromino* activeTetrimino = player->getActiveTetrimino();
            if (activeTetrimino != nullptr) {
                std::lock_guard<std::recursive_mutex> lock3(gameboardMutex);
                bool wasBlockMoved = activeTetrimino->moveDown(board);
                std::cout << "Move Down: " << wasBlockMoved << "\n";
                // bool wasBlockMoved = true;
                if (wasBlockMoved == false) {
                    player->setActiveTetrimino(nullptr);
                    std::lock_guard<std::recursive_mutex> lock4(gameboardMutex);
                    activeTetrimino->freezeToBoard(board);
                    delete activeTetrimino;

                }
            }
            std::lock_guard<std::recursive_mutex> lock5(gameboardMutex);
            board->checkFilledRows();
        }
    }
}

int main()
{
    /* Should be obtained from main menu */
    // TODO: Non-square dimensions are broken
    const int GAMEBOARD_HEIGHT = 16;
    const int GAMEBOARD_WIDTH = 12;
    Block block(0, 0, sf::Color::Blue);
    const int BLOCK_WIDTH = block.getWidth();
    const int BLOCK_HEIGHT = block.getHeight();
    int playerCount = 1;

    std::vector<Player*> players;
    Player player1(sf::Color::Blue, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    players.push_back(&player1);
    // Max 2 players for now
    if (playerCount > 1) {
        Player player2(sf::Color::Blue, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
        players.push_back(&player2);
    }

    // Init
    InputHandler inputHandler;
    Gameboard board(GAMEBOARD_HEIGHT, GAMEBOARD_WIDTH);

    Window gameWindow(
        GAMEBOARD_WIDTH * BLOCK_WIDTH,
        GAMEBOARD_HEIGHT * BLOCK_HEIGHT, "Concurrent Tetris");

    sf::Event event;

    // Start the logic thread
    std::thread gameThread(gameLogicThread, players, &board, &inputHandler);

    while (gameWindow.isOpen()) {
        while (gameWindow.pollEvent(event)) {
            std::lock_guard<std::recursive_mutex> lock1(gameboardMutex);
            inputHandler.processInput(players, &board, event);
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
        /* Main loop */
        gameWindow.clear();
        std::lock_guard<std::recursive_mutex> lock(gameboardMutex);
        gameWindow.drawGameboard(&board, BLOCK_WIDTH, BLOCK_HEIGHT);
        gameWindow.drawScoreboard(69, 69);
        gameWindow.display();
    }
    terminateThreads = true;
    return 0;
}
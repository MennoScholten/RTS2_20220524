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
#include "include/MainMenu.h"


std::recursive_mutex gameboardMutex;
bool terminateThreads = false;

void gameLogicThread(std::vector<Player*> players, Gameboard* board, InputHandler* inputHandler)
{
    const int GAME_TICK_DURATION = 500; // ms

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
                tetromino->createRandomTetromino(0, board->getSizeY() / 2, player->getColor());
                std::lock_guard<std::recursive_mutex> lock2(gameboardMutex);
                bool gameOver = tetromino->addToGameBoard(board);
                if (!gameOver) {
                    std::cout << "Game Over!";
                    return;
                }
                player->setActiveTetrimino(tetromino);
            }
        }

        // Game tick delay
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
            player->setScore(player->getScore() + board->checkFilledRows());
            board->resetRowsScoreCounter();
            std::cout << player->getScore();
        }
    }
}

void updateTetrominoPosition(Player* player, Gameboard* board) {
    Tetromino* activeTetrimino = player->getActiveTetrimino();
    if (activeTetrimino != nullptr) {
        std::lock_guard<std::recursive_mutex> lock(gameboardMutex);
        activeTetrimino->updatePosition(board);
    }
}

int main()
{
    MainMenu menu;
    bool menuResult = menu.showMainMenu();
    if (menuResult == false) {
        return 0;
    }
    MainMenu::MainMenuData userSelection = menu.getMainMenuData();
    const int GAMEBOARD_HEIGHT = userSelection.boardDimensions.y;
    const int GAMEBOARD_WIDTH = userSelection.boardDimensions.x;
    int playerCount = userSelection.numberOfPlayers;
    Block block(0, 0, sf::Color::Blue);
    const int BLOCK_WIDTH = block.getWidth();
    const int BLOCK_HEIGHT = block.getHeight();

    std::vector<Player*> players;
    Player* player1 = new Player(userSelection.player1Color, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    players.push_back(player1);
    if (playerCount >= 2) {
        Player* player2 = new Player(userSelection.player2Color, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
        players.push_back(player2);
    }

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
                terminateThreads = true;
            }
        }
        // Update Tetromino positions before drawing
        for (Player* player : players) {
            updateTetrominoPosition(player, &board);
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
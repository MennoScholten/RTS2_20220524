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
#include <time.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include "include/MainMenu.h"


bool terminateThreads = false;

void gameLogicThread(std::vector<Player*> players, Gameboard* board, InputHandler* inputHandler)
{
    const int GAME_TICK_DURATION = 500; // ms

    struct timespec job_start,job_end, timer, sleep;
    // timer.tv_sec = 0;
    timer.tv_nsec = GAME_TICK_DURATION * 1000000;

    timespec_get(&job_start, TIME_UTC);
    while (true) { 
        
        if (terminateThreads == true) {
            return;
        }
        // if player doesnt have an active block, spawn a block for player
        for (Player* player : players) {
            if (player->getActiveTetrimino() == nullptr) {
                Tetromino* tetromino = new Tetromino();
                sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
                tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
                bool gameOver = tetromino->addToGameBoard(board);
                if (!gameOver) {
                    std::cout << "Game Over!";
                    return;
                }
                player->setActiveTetrimino(tetromino);
            }
        }

        // Game tick delay
        (void) timespec_get(&job_end, TIME_UTC);
        sleep.tv_nsec = timer.tv_nsec - (job_end.tv_nsec - job_start.tv_nsec);
        std::this_thread::sleep_for(std::chrono::nanoseconds(sleep.tv_nsec));
        std::cout << "Sleeptime: " << sleep.tv_nsec << std::endl;
        (void) timespec_get(&job_start, TIME_UTC);

        // Move the active tetrimino down
        for (Player* player : players) {
            Tetromino* activeTetrimino = player->getActiveTetrimino();
            if (activeTetrimino != nullptr) {
                bool wasBlockMoved = activeTetrimino->moveDown(board);
                std::cout << "Move Down: " << wasBlockMoved << "\n";
                // bool wasBlockMoved = true;
                if (wasBlockMoved == false) {
                    player->setActiveTetrimino(nullptr);
                    activeTetrimino->freezeToBoard(board);
                    delete activeTetrimino;
                }
            }
            int clearedRows = board->checkFilledRows();
            if (clearedRows >= 1) {
                player->setScore(player->getScore() + std::pow(6, clearedRows));
            }
            std::cout << player->getScore();
        }
    }
}

void updateTetrominoPosition(Player* player, Gameboard* board) {
    Tetromino* activeTetrimino = player->getActiveTetrimino();
    if (activeTetrimino != nullptr) {
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
    Gameboard board(GAMEBOARD_HEIGHT, GAMEBOARD_WIDTH); // Real gameboard object that holds blocks
    /* Gameboard graphical representation vector */
    std::vector<std::vector<sf::Color>> colorVector(GAMEBOARD_HEIGHT, std::vector<sf::Color>(GAMEBOARD_WIDTH));
    Window gameWindow(
        GAMEBOARD_WIDTH * BLOCK_WIDTH,
        GAMEBOARD_HEIGHT * BLOCK_HEIGHT, "Concurrent Tetris");

    sf::Event event;

    // Start the logic thread
    std::thread gameThread(gameLogicThread, players, &board, &inputHandler);
    
    time_t startSeconds;
    startSeconds = time(NULL);
 
    while (gameWindow.isOpen()) {
        time_t gameSeconds;
        gameSeconds = time(NULL) - startSeconds;
        while (gameWindow.pollEvent(event)) {
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
        board.getGameboardCopy(&colorVector);
        gameWindow.drawGameboard(colorVector, BLOCK_WIDTH, BLOCK_HEIGHT);
        if (players.size() > 1) {
            gameWindow.drawScoreboard(players[0]->getScore(), players[1]->getScore(), int(gameSeconds));
        }
        else {
            gameWindow.drawScoreboard(players[0]->getScore(), 0, int(gameSeconds));
        }
        gameWindow.display();
    }
    terminateThreads = true;
    return 0;
}

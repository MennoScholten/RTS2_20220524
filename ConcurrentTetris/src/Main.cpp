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

const bool MAIN_MENU = false;

void spawnTetromino(Player* player, Gameboard* board) {
    // Adds new tetromino to the specified player and checks for game over.
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

void moveTetrominoDown(Player* player, Gameboard* board) {
    // Moves the specified player's active Tetromino down.
    bool wasBlockMoved = player->getActiveTetrimino()->moveDown(board);
    std::cout << "Move Down: " << wasBlockMoved << "\n";
    if (wasBlockMoved == false) {
        player->getActiveTetrimino()->freezeToBoard(board);
        delete player->getActiveTetrimino();
        player->setActiveTetrimino(nullptr);
    }
}

void gameLogic(Player* player, Gameboard* board, int& currentCleared) {
    // TASK: Spawn Tetromino
    if (player->getActiveTetrimino() == nullptr) {
        spawnTetromino(player, board);
    }

    // TASK: Move Tetromino down
    Tetromino* activeTetrimino = player->getActiveTetrimino();
    if (activeTetrimino != nullptr) {
        moveTetrominoDown(player, board);
    }

    // TASK: Clear filled rows
    int clearedRows = board->checkFilledRows();
    currentCleared = clearedRows;
    if (clearedRows >= 1) {
        player->setScore(player->getScore() + std::pow(6, clearedRows));
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
    int currentCleared = 0;
    MainMenu menu;
    InputHandler inputHandler;
    if (MAIN_MENU == true) {
        bool menuResult = menu.showMainMenu();
        if (menuResult == false) {
            return 0;
        }
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

    Gameboard board(GAMEBOARD_HEIGHT, GAMEBOARD_WIDTH); // Real gameboard object that holds blocks
    Window gameWindow(
        GAMEBOARD_WIDTH * BLOCK_WIDTH,
        GAMEBOARD_HEIGHT * BLOCK_HEIGHT, "Concurrent Tetris");

    sf::Event event;
    
    time_t startSeconds;
    startSeconds = time(NULL);
 
    // Required for printing fps to console
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    // Required to execute gameLogic at interval
    sf::Clock gameClock;
    gameClock.restart();
    

    // Limit the framerate of the system.
    gameWindow.setFramerateLimit(0);

    // Main loop
    while (gameWindow.isOpen()) {
        time_t gameSeconds;
        gameSeconds = time(NULL) - startSeconds;

        // TASK: Polling Server
        inputHandler.processInput(players[0], &board);

        // The SFML event server
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
                return 0;
            }
        }
        
        // Print FPS to console
        currentTime = clock.getElapsedTime();
        float fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        std::cout << "fps =" << floor(fps) << std::endl;
        previousTime = currentTime;

        /* Main loop */
        gameWindow.clear();

        // TASK: Update tetromino position
        for (Player* player : players) {
            updateTetrominoPosition(player, &board);
        }

        // TASK: Get Gameboard
        std::vector<std::vector<Block*>> currentGameboard = board.getGameboard();

        // TASK: Draw Scoreboard
        gameWindow.drawScoreboard(players[0]->getScore(), 0, int(gameSeconds));

        // TASK: Draw Gameboard
        gameWindow.drawGameboard(currentGameboard, BLOCK_WIDTH, BLOCK_HEIGHT);

        // TASK: Game Tick
        const int GAME_TICK_DURATION = 500; // Game tick self-loop (milliseconds)
        auto gameCurrentTime = gameClock.getElapsedTime().asMilliseconds();
        if (gameCurrentTime > GAME_TICK_DURATION) {
            gameLogic(players[0], &board, currentCleared);
            gameClock.restart();
        }

        // Special effects (Task maybe?)
        gameWindow.setNumberSprite(currentCleared);

        // SFML Draw
        gameWindow.display();
    }
    return 0;
}

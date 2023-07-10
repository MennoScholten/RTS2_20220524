#include <iostream>
#include <gtest/gtest.h>
#include "../src/include/InputHandler.h"
#include <chrono>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdio.h>
#include "../src/include/Window.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

std::string GetCurrentWorkingDirectory() {
std::string cwd;
#ifdef _WIN32
    char buffer[FILENAME_MAX];
    GetCurrentDirectoryA(FILENAME_MAX, buffer);
    cwd = buffer;
#else
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, FILENAME_MAX) != nullptr)
        cwd = buffer;
#endif
    return cwd;
}

void saveMeasurementsToFile(const std::vector<long long>& timeArray, const std::string& fileName)
{
    std::ofstream outputFile(fileName);
    if (outputFile.is_open())
    {
        for (const auto& duration : timeArray)
        {
            outputFile << duration << std::endl;
        }
        outputFile.close();

        std::cout << "WCET measurements file saved to: " << GetCurrentWorkingDirectory() + fileName << std::endl;
    }
    else
    {
        std::cout << "Unable to open file, results not written!" << std::endl;
    }
}

void printStatistics(const std::vector<long long>& timeArray, int numIterations, const std::string& testName)
{
    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);
    auto averageDuration = sumDuration / numIterations;

    std::cout << testName << " | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << averageDuration << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;
}


TEST(TetrisTests, PollingWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(10, 20);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();
        
        // Call the method
        inputHandler.processInput(player, board);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "PollingWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "PollingWCET.txt");
}

TEST(TetrisTests, MoveTetrominoWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    if (Globals::THREADED) {
        numIterations = 1000;
    }

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(20, 20);
    Tetromino* tetromino = new Tetromino();
    tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
    tetromino->addToGameBoard(board);
    player->setActiveTetrimino(tetromino);
    player->getActiveTetrimino()->moveDown(board);
    player->getActiveTetrimino()->moveDown(board);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // Move tetromino left, right, rotate
        player->getActiveTetrimino()->moveLeft(board);
        player->getActiveTetrimino()->moveRight(board);
        player->getActiveTetrimino()->rotateClockwise(board);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "MoveTetrominoWCET (LEFT + RIGHT + ROTATE)");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "MoveTetrominoWCET.txt");
}

TEST(TetrisTests, UpdateTetrominoPositionWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    if (Globals::THREADED) {
        numIterations = 1000;
    }

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(20, 20);
    Tetromino* tetromino = new Tetromino();
    tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
    tetromino->addToGameBoard(board);
    player->setActiveTetrimino(tetromino);
    player->getActiveTetrimino()->moveDown(board);
    player->getActiveTetrimino()->moveDown(board);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // update position
        player->getActiveTetrimino()->updatePosition(board);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "UpdateTetrominoPositionWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "UpdateTetrominoPositionWCET.txt");
}

TEST(TetrisTests, GetGameboardWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(10, 20);
    Tetromino* tetromino = new Tetromino();
    tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
    tetromino->addToGameBoard(board);
    player->setActiveTetrimino(tetromino);
    player->getActiveTetrimino()->moveDown(board);
    player->getActiveTetrimino()->moveDown(board);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // get gameboard
        board->getGameboard();

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "GetGameboardWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "GetGameboardWCET.txt");
}

TEST(TetrisTests, DISABLED_DrawScoreboardWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 500;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(10, 20);
    Tetromino* tetromino = new Tetromino();
    tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
    tetromino->addToGameBoard(board);
    player->setActiveTetrimino(tetromino);
    player->getActiveTetrimino()->moveDown(board);
    player->getActiveTetrimino()->moveDown(board);
    Window gameWindow(20 * 30, 10 * 30, "DrawScoreboardWCET");
    gameWindow.setFramerateLimit(0);

    for (int i = 0; i < numIterations; i++)
    {
        gameWindow.clear();
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // draw
        gameWindow.drawScoreboard(player->getScore(), 0, i);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
        gameWindow.display();
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "DrawScoreboardWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "DrawScoreboardWCET.txt");
}

TEST(TetrisTests, DISABLED_DrawGameboardWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 500;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Window gameWindow(20 * 30, 10 * 30, "DrawGameboardWCET");
    gameWindow.setFramerateLimit(0);

    for (int i = 0; i < numIterations; i++)
    {
        Player* player = new Player(sf::Color(rand() % 255, rand() % 255, rand() % 255), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
        Gameboard* board = new Gameboard(10, 20);
        Tetromino* tetromino = new Tetromino();
        tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, player->getColor());
        tetromino->addToGameBoard(board);
        player->setActiveTetrimino(tetromino);
        player->getActiveTetrimino()->moveDown(board);
        player->getActiveTetrimino()->moveDown(board);
        gameWindow.clear();
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // draw
        gameWindow.drawGameboard(board->getGameboard(), 30, 30);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
        gameWindow.display();
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "DrawGameboardWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "DrawGameboardWCET.txt");
}

TEST(TetrisTests, SpawnTetrominoWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS

    for (int i = 0; i < numIterations; i++)
    {
        Player* player = new Player(sf::Color(rand() % 255, rand() % 255, rand() % 255), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
        Gameboard* board = new Gameboard(10, 20);
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // Spawn tetromino
        player->spawnTetromino(board);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "SpawnTetrominoWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "SpawnTetrominoWCET.txt");
}

TEST(TetrisTests, CheckBlockCollisionWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    if (Globals::THREADED) {
        numIterations = 1000;
    }

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    Player* player = new Player(sf::Color::Red, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
    Gameboard* board = new Gameboard(20, 20);
    Tetromino* tetromino = new Tetromino();
    tetromino->blockO(1, 1, player->getColor());
    tetromino->addToGameBoard(board);
    tetromino->freezeToBoard(board);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // Check no collision and with collision
        board->checkCollision(0, 0);
        board->checkCollision(1, 1);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "CheckBlockCollisionWCET (NO COLLISION + COLLISION)");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "CheckBlockCollisionWCET.txt");
}

TEST(TetrisTests, CheckFilledRowsWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    int GAMEBOARD_COLUMNS = 20;
    Gameboard* board = new Gameboard(20, GAMEBOARD_COLUMNS);
    for (int i = 0; i < GAMEBOARD_COLUMNS; i++) {
        Block* block = new Block(0, 0, sf::Color::Blue);
        block->setAlive(false);
        board->addBlock(19, i, block);
    }

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // check for filled row
        board->getFilledRows();
        

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "CheckFilledRowsWCET (1 ROW FILLED)");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "CheckFilledRowsWCET.txt");
}

TEST(TetrisTests, RemoveBlockWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS

    for (int i = 0; i < numIterations; i++)
    {
        int GAMEBOARD_COLUMNS = 20;
        Gameboard* board = new Gameboard(20, GAMEBOARD_COLUMNS);
        for (int i = 0; i < GAMEBOARD_COLUMNS; i++) {
            Block* block = new Block(0, 0, sf::Color::Blue);
            block->setAlive(false);
            board->addBlock(19, i, block);
        }

        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // check for filled row
        board->removeBlock(19, 0);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "RemoveBlockWCET");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "RemoveBlockWCET.txt");
}

TEST(TetrisTests, MoveBlockWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    // PREPARATIONS
    int GAMEBOARD_COLUMNS = 20;
    Gameboard* board = new Gameboard(20, GAMEBOARD_COLUMNS);
    Block* block = new Block(0, 0, sf::Color::Blue);
    block->setAlive(false);
    board->addBlock(0, 0, block);

    for (int i = 0; i < numIterations; i++)
    {
        // START MEASURING
        auto iterationStartTime = std::chrono::high_resolution_clock::now();

        // move block across the board and back
        board->moveBlock(block, 19, 19);
        board->moveBlock(block, 0, 0);

        // STOP MEASURING
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    // Print results to console
    printStatistics(timeArray, numIterations, "MoveBlockWCET (2 MOVE OPERATION)");

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "MoveBlockWCET.txt");
}

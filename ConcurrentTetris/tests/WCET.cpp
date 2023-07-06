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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "PollingWCET | Iterations: " << numIterations << " | " << std::endl;
    std::cout 
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "PollingWCET.txt");
}

TEST(TetrisTests, MoveTetrominoWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 10000;

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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "MoveTetrominoWCET (LEFT + RIGHT + ROTATE) | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "MoveTetrominoWCET.txt");
}

TEST(TetrisTests, UpdateTetrominoPositionWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 10000;

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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "UpdateTetrominoPositionWCET | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "UpdateTetrominoPositionWCET.txt");
}

TEST(TetrisTests, GetGameboardWCET)
{
    InputHandler inputHandler;

    // How many measurements to take
    const int numIterations = 1000;

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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "GetGameboardWCET | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "GetGameboardWCET.txt");
}

TEST(TetrisTests, DrawScoreboardWCET)
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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "DrawScoreboardWCET | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "DrawScoreboardWCET.txt");
}

TEST(TetrisTests, DrawGameboardWCET)
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

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout << "DrawGameboardWCET | Iterations: " << numIterations << " | " << std::endl;
    std::cout
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    saveMeasurementsToFile(timeArray, "DrawGameboardWCET.txt");
}


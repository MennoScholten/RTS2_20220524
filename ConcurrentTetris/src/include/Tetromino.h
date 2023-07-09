#pragma once
#include "Gameboard.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Globals.h"
#include <algorithm>
#include <random>

class Tetromino
{
public:
    Tetromino();
    bool addToGameBoard(Gameboard* gameboard);
    void rotateClockwise(Gameboard* board);
    void moveRight(Gameboard* board);
    void moveLeft(Gameboard* board);
    bool moveDown(Gameboard* board);
    void moveDrop(Gameboard* board);
    void freezeToBoard(Gameboard* board);
    sf::Vector2i getPivotPoint();
    void setGridPosition(int x, int y);
    bool checkIfMoveIsValid(Gameboard* board, int tetrominoNewX, int tetrominoNewY, bool rotation = false);
    void updatePosition(Gameboard* board);

    void createRandomTetromino(int x, int y, sf::Color color);
    void blockI(int x, int y, sf::Color color);
    void blockL(int x, int y, sf::Color color);
    void blockJ(int x, int y, sf::Color color);
    void blockZ(int x, int y, sf::Color color);
    void blockS(int x, int y, sf::Color color);
    void blockT(int x, int y, sf::Color color);
    void blockO(int x, int y, sf::Color color);

private:
    std::vector<Block*> blocks;
    sf::Vector2i gridPosition;
    sf::Vector2i pivotPoint;
    sf::Vector2i pivotPointOffset;
    sf::Color color;
};
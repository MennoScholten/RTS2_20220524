#pragma once
#include "Gameboard.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"

class Tetromino
{
public:
    Tetromino(int x, int y, sf::Color color);
    void addToGameBoard(Gameboard* gameboard);
    void rotateClockwise(Gameboard* board);
    void moveRight(Gameboard* board);
    void moveLeft(Gameboard* board);
    bool moveDown(Gameboard* board);
    void freezeToBoard(Gameboard* board);
    sf::Vector2i getPivotPoint();
    void setGridPosition(int x, int y);
    sf::Vector2i getGridPosition();
    
    Tetromino blockI(int x, int y, sf::Color color);
    Tetromino blockL(int x, int y, sf::Color color);
    Tetromino blockJ(int x, int y, sf::Color color);
    Tetromino blockZ(int x, int y, sf::Color color);
    Tetromino blockS(int x, int y, sf::Color color);
    Tetromino blockT(int x, int y, sf::Color color);
    Tetromino blockO(int x, int y, sf::Color color);

private:
    std::vector<Block*> blocks;
    sf::Vector2i gridPosition;
    sf::Vector2i pivotPoint;
    sf::Vector2i pivotPointOffset;
    sf::Color color;
};
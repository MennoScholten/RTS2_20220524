#pragma once
#include "Gameboard.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"

class Tetromino
{
public:
    Tetromino(int x, int y, sf::Color color, Gameboard* gameboard);
    void addToGameBoard(Gameboard* gameboard);
    void rotateClockwise(Gameboard* board);
    void moveRight(Gameboard* board);
    void moveLeft(Gameboard* board);
    sf::Vector2i getPivotPoint();
    void setGridPosition(int x, int y);
    sf::Vector2i getGridPosition();
    
    Tetromino blockI(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockL(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockJ(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockZ(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockS(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockT(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockO(int x, int y, sf::Color color, Gameboard* gameboard);

private:
    std::vector<Block*> blocks;
    sf::Vector2i gridPosition;
    sf::Vector2i pivotPoint;
    sf::Vector2i pivotPointOffset;
    sf::Color color;
};
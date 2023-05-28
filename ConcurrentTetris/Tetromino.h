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
    Tetromino blockO(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockL(int x, int y, sf::Color color, Gameboard* gameboard);
    Tetromino blockT(int x, int y, sf::Color color, Gameboard* gameboard);

private:
    std::vector<Block*> blocks;
    int gridPositionX;
    int gridPositionY;
    sf::Vector2i pivotPoint;
    sf::Color color;
};
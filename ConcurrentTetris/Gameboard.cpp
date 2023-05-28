#include "Gameboard.h"
#include <iostream>

// Constructor
Gameboard::Gameboard(int x, int y) {
    board.resize(y, std::vector<Block*>(x));
    Gameboard::x = x;
    Gameboard::y = y;
}

std::vector<std::vector<Block*>> Gameboard::getGameboard() {
    return Gameboard::board;
}

int Gameboard::getColumns() const
{
    return Gameboard::x;
}

int Gameboard::getRows() const
{
    return Gameboard::y;
}

void Gameboard::addBlock(int x, int y, Block* blockObject) {
    Gameboard::board[y][x] = blockObject;
    blockObject->setPosition(x, y);
}

bool Gameboard::isOccupied(int x, int y)
{
    if (x < 0 || x >= Gameboard::board.size() || y < 0 || y >= Gameboard::board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }

    return Gameboard::board[x][y] != nullptr;
}

void Gameboard::moveBlock(Block* block, int newX, int newY) {

    if (this->board[block->getPositionY()][block->getPositionX()] == block) {
        this->board[block->getPositionY()][block->getPositionX()] = nullptr;
        this->board[newY][newX] = block;
    }
    else {
        this->board[newY][newX] = block;
    }
}

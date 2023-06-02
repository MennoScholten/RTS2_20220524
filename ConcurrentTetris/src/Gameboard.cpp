#include "include/Gameboard.h"
#include <iostream>

// Constructor
Gameboard::Gameboard(int x, int y) {
    board.resize(x, std::vector<Block*>(y));
    this->x = x;
    this->y = y;
}

const std::vector<std::vector<Block*>>& Gameboard::getGameboard() const {
    return this->board;
}

int Gameboard::getSizeX() const
{
    return this->x;
}

int Gameboard::getSizeY() const
{
    return this->y;
}

void Gameboard::addBlock(int x, int y, Block* blockObject) {
    this->board[x][y] = blockObject;
    blockObject->setPosition(x, y);
}

void Gameboard::createLockedBlock(Block* playerBlock) {
    Block* block = new Block(playerBlock->getPositionX(), playerBlock->getPositionY(), playerBlock->getColor());
    block->setAlive(false);
    this->addBlock(playerBlock->getPositionX(), playerBlock->getPositionY(), block);
}

bool Gameboard::isOccupied(int x, int y)
/* Used for drawing purposes */

{
    if (x < 0 || x >= this->board.size() || y < 0 || y >= this->board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }
    return this->board[x][y] != nullptr;
}

bool Gameboard::checkCollision(int x, int y)
{
    if (x < 0 || x >= this->board.size() || y < 0 || y >= this->board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }
    // The cell is a null pointer means its empty
    if (this->board[x][y] == nullptr) {
        return false;
    }
    // If not nullpointer, check if it is a player-controlled block
    return this->board[x][y]->getAlive() == false;
}

void Gameboard::moveBlock(Block* block, int newX, int newY) {
    if (this->board[block->getPositionX()][block->getPositionY()] == block) {
        this->board[block->getPositionX()][block->getPositionY()] = nullptr;
        this->board[newX][newY] = block;
        block->setPosition(newX, newY);
    }
    else {
        this->board[newX][newY] = block;
        block->setPosition(newX, newY);
    }
}

int Gameboard::checkFilledRows() {
    for (int row = this->board.size() - 1; row >= 0; row--) {
        // Check if any elements in row are nullptr
        if (std::none_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block == nullptr; })) {
            // Check if any elements in row are still player controlled
            if (std::all_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block->getAlive() == false; })) {
                this->clearedRows++;
                for (Block* block : this->board[row]) {
                    this->board[block->getPositionX()][block->getPositionY()] = nullptr;
                    delete block;
                }
                this->moveAllBlocksDown(row);
                this->checkFilledRows();
            }
        }
    }
    return this->clearedRows;
}

void Gameboard::moveAllBlocksDown(int row) {
    for (int i = row - 1; i >= 0; i--) {
        for (Block* block : this->board[i]) {
            if (block != nullptr) {
                this->moveBlock(block, block->getPositionX() + 1, block->getPositionY());
            }
        }
    }
}

void Gameboard::resetRowsScoreCounter() {
    this->clearedRows = 0;
}

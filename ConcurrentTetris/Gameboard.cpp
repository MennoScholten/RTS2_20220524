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

void Gameboard::createLockedBlock(Block* playerBlock) {
    Block* block = new Block(playerBlock->getPositionX(), playerBlock->getPositionY(), playerBlock->getColor());
    block->setAlive(false);
    this->addBlock(playerBlock->getPositionX(), playerBlock->getPositionY(), block);
}

bool Gameboard::isOccupied(int x, int y)
/* Used for drawing purposes */

{
    if (x < 0 || x >= Gameboard::board.size() || y < 0 || y >= Gameboard::board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }
    return this->board[x][y] != nullptr;
}

bool Gameboard::checkCollision(int x, int y)
{
    if (x < 0 || x >= Gameboard::board.size() || y < 0 || y >= Gameboard::board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }
    // The cell is a null pointer means its empty
    if (this->board[y][x] == nullptr) {
        return false;
    }
    // If not nullpointer, check if it is a player-controlled block
    return this->board[y][x]->getAlive() == false;
}

void Gameboard::moveBlock(Block* block, int newX, int newY) {
    if (this->board[block->getPositionY()][block->getPositionX()] == block) {
        this->board[block->getPositionY()][block->getPositionX()] = nullptr;
        this->board[newY][newX] = block;
        block->setPosition(newX, newY);
    }
    else {
        this->board[newY][newX] = block;
        block->setPosition(newX, newY);
    }
}

int Gameboard::checkFilledRows() {
    int filledRows = 0;
    for (int row = this->board.size() - 1; row >= 0; row--) {
        // Check if any elements in row are nullptr
        if (std::none_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block == nullptr; })) {
            // Check of any elements in row are still player controlled
            if (std::all_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block->getAlive() == false; })) {
                std::cout << "FULL LINE! ";
                for (Block* block : this->board[row]) {
                    this->board[block->getPositionY()][block->getPositionX()] = nullptr;
                    delete block;
                }
                this->moveAllBlocksDown(row);
                this->checkFilledRows();
            }
        }
    }
    return 0;
}

void Gameboard::moveAllBlocksDown(int row) {
    for (int i = row - 1; i >= 0; i--) {
        for (Block* block : this->board[i]) {
            if (block != nullptr) {
                this->moveBlock(block, block->getPositionX(), block->getPositionY() + 1);
            }
        }
    }
}
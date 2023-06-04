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

void Gameboard::getGameboardCopy(std::vector<std::vector<sf::Color>>* colorVector)
{
    std::lock_guard<std::mutex> lock(this->boardMutex);
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            if (board[i][j] != nullptr) {
                (*colorVector)[i][j] = this->board[i][j]->getColor();
            }
            else {
                (*colorVector)[i][j] = sf::Color::Transparent;
            }
        }
    }
}

int Gameboard::getSizeY() const
{
    return this->y;
}

void Gameboard::addBlock(int x, int y, Block* blockObject) {
    std::lock_guard<std::mutex> lock(this->boardMutex);
    this->board[x][y] = blockObject;
    blockObject->setPosition(x, y);
}

void Gameboard::createLockedBlock(Block* playerBlock) {
    Block* block = new Block(playerBlock->getPositionX(), playerBlock->getPositionY(), playerBlock->getColor());
    block->setAlive(false);
    this->addBlock(playerBlock->getPositionX(), playerBlock->getPositionY(), block);
}

bool Gameboard::checkCollision(int x, int y)
{
    std::lock_guard<std::mutex> lock(this->boardMutex);
    if (x < 0 || x >= this->board.size() || y < 0 || y >= this->board[0].size())
    {
        return true; // Invalid indices, consider it as occupied
    }
    // The cell is a null pointer means its empty
    if (this->board[x][y] == nullptr) {
        return false;
    }
    // If not nullpointer, check if it is a player-controlled block
    return this->board[x][y]->getAlive() == false;
}

void Gameboard::moveBlock(Block* block, int newX, int newY) {
    std::lock_guard<std::mutex> lock(this->boardMutex);
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
    std::unique_lock<std::mutex> lock(this->boardMutex);
    int clearedRows = 0;
    int row = this->x - 1;
    while (row >= 0) {
        // Check if any elements in row are nullptr
        if (std::none_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block == nullptr; })) {
            // Check if any elements in row are still player controlled
            if (std::all_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block->getAlive() == false; })) {
                clearedRows++;
                for (Block* block : this->board[row]) {
                    this->board[block->getPositionX()][block->getPositionY()] = nullptr;
                    delete block;
                }
                lock.unlock();
                this->moveAllBlocksDown(row);
                lock.lock();
                row = this->x - 1;
                continue;
            }
        }
        row--; // Move to the next row
    }
    return clearedRows;
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

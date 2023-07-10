#include "include/Gameboard.h"
#include <iostream>

// Constructor
Gameboard::Gameboard(int x, int y) {
    board.resize(x, std::vector<Block*>(y));
    this->x = x;
    this->y = y;
}

const std::vector<std::vector<Block*>> Gameboard::getGameboard() const {
    return this->board;
}

void Gameboard::addBlock(int x, int y, Block* blockObject) {
    // std::lock_guard<std::mutex> lock(this->boardMutex);
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
    // std::lock_guard<std::mutex> lock(this->boardMutex);
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

std::vector<int> Gameboard::getFilledRows() {
    // Returns array of rows, 
    std::vector<int> filledRows;
    for (int row = 0; row < this->x; row++) {
        bool isFilled = std::all_of(this->board[row].begin(), this->board[row].end(), [](Block* block) { return block != nullptr; });
        filledRows.push_back(isFilled ? 1 : 0);
    }
    return filledRows;
}

void Gameboard::removeBlock(int x, int y) {
    Block* block = this->board[x][y];
    if (block != nullptr) {
        this->board[x][y] = nullptr;
        delete block;
    }
}

void Gameboard::clearFilledColumn(const std::vector<int> filledRowsVector, int column) {
    int filledRows = std::accumulate(filledRowsVector.begin(), filledRowsVector.end(), decltype(filledRowsVector)::value_type(0));

    if (filledRows > 0) {
        // Remove blocks if they are part of filled row.
        for (int row = this->board.size() - 1; row >= 0; row--) {
            if (filledRowsVector[row] == 1) {
                this->removeBlock(row, column);
            }
        }
        // Start moving blocks down after the first removed row
        int startingRow = this->board.size() - 1;
        while (filledRowsVector[startingRow] != 1) {
            startingRow--;
        }
        // Move blocks down in the column
        for (int row = startingRow; row >= 0; row--) {
            if (this->board[row][column] != nullptr) {
                this->moveBlock(board[row][column], board[row][column]->getPositionX() + filledRows, board[row][column]->getPositionY());
                this->removeBlock(row, column);
            }
        }
    }
}

int Gameboard::clearFilledRowsAndShiftBlocks() {
    // Returns the number of rows cleared
    std::vector<int> filledRowsVector = getFilledRows();
    std::vector<std::thread> threads;

    if (Globals::THREADED) {
        for (int column = 0; column < this->board[0].size(); column++) {
            threads.emplace_back([&, column]() {
                clearFilledColumn(filledRowsVector, column);
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
    }
    else {
        for (int column = 0; column < this->board[0].size(); column++) {
            clearFilledColumn(filledRowsVector, column);
        }
    }

    return std::accumulate(filledRowsVector.begin(), filledRowsVector.end(), decltype(filledRowsVector)::value_type(0));
}

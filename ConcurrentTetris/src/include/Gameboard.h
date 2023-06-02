#pragma once
#include <vector>
#include <iostream>
#include "Block.h"
#include <mutex>

class Gameboard {
private:
    std::vector<std::vector<Block*>> board;
    int x = 0;
    int y = 0;
    void moveAllBlocksDown(int row);
    int clearedRows = 0;

public:
    // Constructor
    Gameboard(int x, int y);

    const std::vector<std::vector<Block*>>& getGameboard() const;
    int getSizeX() const;
    int getSizeY() const;
    bool isOccupied(int x, int y);
    bool checkCollision(int x, int y);
    void addBlock(int x, int y, Block* blockObject);
    void moveBlock(Block* block, int newRow, int newColumn);
    void createLockedBlock(Block* playerBlock);
    int checkFilledRows();
    void resetRowsScoreCounter();
};

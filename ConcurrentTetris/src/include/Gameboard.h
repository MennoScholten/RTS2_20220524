#pragma once
#include <vector>
#include <iostream>
#include "Block.h"
#include <atomic>
#include <mutex>
#include <numeric>
#include "Globals.h"

class Gameboard {
private:
    std::vector<std::vector<Block*>> board;
    std::mutex boardMutex; // Mutex for protecting board access
    std::atomic<int> x{ 0 };
    std::atomic<int> y{ 0 };
    std::atomic<int> aromicRenderArray;
    

public:
    // Constructor
    Gameboard(int x, int y);

    const std::vector<std::vector<Block*>> getGameboard() const;
    std::vector<int> getFilledRows();
    void clearFilledColumn(const std::vector<int> filledRows, int column);
    int clearFilledRowsAndShiftBlocks();
    void removeBlock(int x, int y);
    bool checkCollision(int x, int y);
    void addBlock(int x, int y, Block* blockObject);
    void moveBlock(Block* block, int newRow, int newColumn);
    void createLockedBlock(Block* playerBlock);
    int getSizeY() const { return this->y; }
    int getSizeX() const { return this->x; }
};

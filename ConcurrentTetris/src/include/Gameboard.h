#pragma once
#include <vector>
#include <iostream>
#include "Block.h"
#include <atomic>
#include <mutex>

class Gameboard {
private:
    std::vector<std::vector<Block*>> board;
    std::mutex boardMutex; // Mutex for protecting board access
    std::atomic<int> x = 0;
    std::atomic<int> y = 0;
    std::atomic<int> aromicRenderArray;
    void moveAllBlocksDown(int row);
    

public:
    // Constructor
    Gameboard(int x, int y);

    const std::vector<std::vector<Block*>>& getGameboard() const;
    void getGameboardCopy(std::vector<std::vector<sf::Color>>* colorVector);
    int getSizeX() const;
    int getSizeY() const;
    bool checkCollision(int x, int y);
    void addBlock(int x, int y, Block* blockObject);
    void moveBlock(Block* block, int newRow, int newColumn);
    void createLockedBlock(Block* playerBlock);
    int checkFilledRows();
};

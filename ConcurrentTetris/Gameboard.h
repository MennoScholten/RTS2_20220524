#pragma once
#include <vector>
#include <iostream>
#include "Block.h"

class Gameboard {
private:
    std::vector<std::vector<Block*>> board;
    int x = 0;
    int y = 0;

public:
    // Constructor
    Gameboard(int x, int y);

    std::vector<std::vector<Block*>> getGameboard();
    int getColumns() const;
    int getRows() const;
    bool isOccupied(int x, int y);
    bool checkCollision(int x, int y);
    void addBlock(int x, int y, Block* blockObject);
    void moveBlock(Block* block, int newRow, int newColumn);
};

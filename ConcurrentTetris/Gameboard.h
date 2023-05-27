#pragma once
#include <vector>
#include <iostream>
#include "Block.h"

class Gameboard {
private:
    std::vector<std::vector<Block*>> board;
    int columns = 0;
    int rows = 0;

public:
    // Constructor
    Gameboard(int columns, int rows);

    std::vector<std::vector<Block*>> getGameboard();
    int getColumns() const;
    int getRows() const;
    bool isOccupied(int row, int column);
    void addBlock(int row, int column, Block* blockObject);

};

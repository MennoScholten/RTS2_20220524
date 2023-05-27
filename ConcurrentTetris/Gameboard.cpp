#include "Gameboard.h"

// Constructor
Gameboard::Gameboard(int columns, int rows) {
    board.resize(rows, std::vector<Block*>(columns));
    Gameboard::columns = columns;
    Gameboard::rows = rows;
}

std::vector<std::vector<Block*>> Gameboard::getGameboard() {
    return Gameboard::board;
}

int Gameboard::getColumns() const
{
    return Gameboard::columns;
}

int Gameboard::getRows() const
{
    return Gameboard::rows;
}

void Gameboard::addBlock(int row, int column, Block* blockObject) {
    Gameboard::board[row][column] = blockObject;
}

bool Gameboard::isOccupied(int row, int column)
{
    if (row < 0 || row >= Gameboard::board.size() || column < 0 || column >= Gameboard::board[0].size())
    {
        // Invalid indices, consider it as occupied
        return true;
    }

    return Gameboard::board[row][column] != nullptr;
}

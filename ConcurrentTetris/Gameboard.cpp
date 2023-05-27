#include "Gameboard.h"
#include <iostream>

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

void Gameboard::addTetromino(Tetromino* tetrominoObject)
{
    std::vector<Block*> TetrominoBlocks = tetrominoObject->getBlocks();
    float x, y = 0;
    for (int i = 0; i < TetrominoBlocks.size(); i++) {
        std::cout << "New block added\n";
        TetrominoBlocks[i]->getPosition(x, y);
        std::cout << "Position X: " << x << "\n";
        std::cout << "Position Y: " << y << "\n";
        y = y - TetrominoBlocks[i]->getOriginX();
        x = x - TetrominoBlocks[i]->getOriginY();
        std::cout << "X: " << x << "\n";
        std::cout << "Y: " << y << "\n";

        sf::Transform testTrans = TetrominoBlocks[i]->getBlockTransform();
        sf::Vector2f transf = testTrans.transformPoint(0, 0);

        std::cout << "XTrans: " << transf.x << "\n";
        std::cout << "YTrans: " << transf.y << "\n";

        int col = std::floor(transf.y / TetrominoBlocks[i]->getWidth());
        int row = std::floor(transf.x / TetrominoBlocks[i]->getHeight());

        Gameboard::board[col][row] = TetrominoBlocks[i];
    }
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

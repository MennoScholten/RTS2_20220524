#include "Gameboard.h"

// Constructor
Gameboard::Gameboard(int width, int height) : width(width), height(height) {
    board.resize(height, std::vector<int>(width));
}

std::vector<std::vector<int>> Gameboard::getGameboard() {
    return board;
}

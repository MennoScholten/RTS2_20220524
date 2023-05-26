#pragma once
#include <vector>
#include <iostream>

class Gameboard {
private:
    std::vector<std::vector<int>> board;
    int width;
    int height;

public:
    // Constructor
    Gameboard(int width, int height);

    std::vector<std::vector<int>> getGameboard();

};

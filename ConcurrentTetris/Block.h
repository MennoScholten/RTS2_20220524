#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
    int width; // pixels
    int height; // pixels
    int position_row; // position in gameboard
    int position_column; // position in gameboard

public:
    sf::Color color;
};


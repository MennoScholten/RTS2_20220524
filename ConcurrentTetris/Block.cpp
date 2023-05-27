#include "Block.h"

// Constructor
Block::Block(int row, int col, const sf::Color& blockColor)
{
    position_column = col;
    position_row = row;
    color = blockColor;
    isAlive = false;
}

int Block::getWidth() const
{
    return Block::width;
}

int Block::getHeight() const
{
    return Block::height;
}

sf::Color Block::getColor() const
{
    return Block::color;
}

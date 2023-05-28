#include "Block.h"

// Constructor
Block::Block(int x, int y, sf::Color blockColor)
{
    positionX = x;
    positionY = y;
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

int Block::getPositionX()
{
    return Block::positionX;
}

int Block::getPositionY() 
{
    return Block::positionY;
}

void Block::setPosition(int x, int y)
{
    Block::positionY = y;
    Block::positionX = x;
}
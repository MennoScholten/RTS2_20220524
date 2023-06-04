#include "include/Block.h"

// Constructor
Block::Block(int x, int y, sf::Color blockColor)
    : positionX(x), positionY(y), color(blockColor), isAlive(true)
{
}

int Block::getWidth() const
{
    return this->width;
}

int Block::getHeight() const
{
    return this->height;
}

bool Block::getAlive()
{
    return this->isAlive;
}

void Block::setAlive(bool alive)
{
    this->isAlive = alive;
}

sf::Color Block::getColor() const
{
    return this->color;
}

int Block::getPositionX()
{
    return this->positionX;
}

int Block::getPositionY() 
{
    return this->positionY;
}

void Block::setPosition(int x, int y)
{
    this->positionY = y;
    this->positionX = x;
}
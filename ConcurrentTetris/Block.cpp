#include "Block.h"

// Default Constructor
Block::Block() :
    sf::Drawable()
{
    this->block.setSize(sf::Vector2f(this->width, this->height));
    setColor(sf::Color::Blue);
    this->isAlive = false;
}

// Constructor
Block::Block(int row, int col, const sf::Color blockColor) :
    sf::Drawable()
{
    position_column = col;
    position_row = row;
    color = blockColor;
    isAlive = false;
}

Block::Block(float positionX, float positionY, float originX, float originY, sf::Color blockColor)
{
    this->originX = originX;
    this->originY = originY;
    this->positionX = positionX;
    this->positionY = positionY;
    this->block.setSize(sf::Vector2f(this->width, this->height));
    this->block.setOrigin(sf::Vector2f(this->originX, this->originY));
    this->block.setPosition(sf::Vector2f(this->positionX, this->positionY));
    setPosition(positionX, positionY);
    setOrigin(originX, originY);
    setColor(blockColor);
}


void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(block, states);
}

int Block::getWidth() const
{
    return this->width;
}

int Block::getHeight() const
{
    return this->height;
}

sf::Color Block::getColor() const
{
    return this->color;
}

void Block::getPosition(float& x, float& y)
{
    sf::Vector2f Position = this->block.getPosition();
    x = Position.x;
    y = Position.y;
}

float Block::getPositionX()
{
    sf::Vector2f Position = this->block.getPosition();
    return Position.x;
}

float Block::getPositionY()
{
    sf::Vector2f Position = this->block.getPosition();
    return Position.y;
}

void Block::getOrigin(float& x, float& y)
{
    sf::Vector2f Origin = this->block.getOrigin();
    x = Origin.x;
    y = Origin.y;
}

float Block::getOriginX()
{
    sf::Vector2f Origin = this->block.getOrigin();
    return Origin.x;
}

float Block::getOriginY()
{
    sf::Vector2f Origin = this->block.getOrigin();
    return Origin.y;
}

void Block::setPosition(float x, float y)
{
    this->positionX = x;
    this->positionY = y;
    this->block.setPosition(sf::Vector2f(this->positionX, this->positionY));
}

void Block::setPositionX(float x)
{
    this->positionX = x;
    this->block.setPosition(sf::Vector2f(this->positionX, this->positionY));
}

void Block::setPositionY(float y)
{
    this->positionY = y;
    this->block.setPosition(sf::Vector2f(this->positionX, this->positionY));
}

void Block::setOrigin(float x, float y)
{
    this->originX = x;
    this->originY = y;
    this->block.setOrigin(sf::Vector2f(this->originX, this->originY));
}

void Block::setOriginX(float x)
{
    this->originX = x;
    this->block.setOrigin(sf::Vector2f(this->originX, this->originY));
}

void Block::setOriginY(float y)
{
    this->originY = y;
    this->block.setOrigin(sf::Vector2f(this->originX, this->originY));
}

void Block::setColor(const sf::Color blockColor)
{
    this->color = blockColor;
    this->block.setFillColor(this->color);
    this->block.setOutlineColor(this->color);
}

void Block::moveBlock(float x, float y)
{
    this->block.move(sf::Vector2f(x, y));
}

void Block::rotateBlock(float a)
{
    this->block.rotate(a);
}

sf::Transform Block::getBlockTransform()
{
    return this->block.getTransform();
}



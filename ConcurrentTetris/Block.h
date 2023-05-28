#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
    int width = 30; // pixels
    int height = 30; // pixels
    int positionY = 0; // relative_position
    int positionX = 0; // relative_position
    sf::Color color = sf::Color::Transparent;
    bool isAlive = false;

public:
    // Constructors
    Block(int y, int x, sf::Color blockColor);

    // Accessors
    int getWidth() const;
    int getHeight() const;
    sf::Color getColor() const;

    // Modifiers
    void setColor(const sf::Color& blockColor);
    int getPositionX();
    int getPositionY();
    void setPosition(int x, int y);
};
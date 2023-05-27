#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
    int width = 30; // pixels
    int height = 30; // pixels
    int position_row = 0; // relative_position
    int position_column = 0; // relative_position
    sf::Color color = sf::Color::Transparent;
    bool isAlive = false;

public:
    // Constructors
    Block(int row, int col, const sf::Color& blockColor);

    // Accessors
    int getWidth() const;
    int getHeight() const;
    sf::Color getColor() const;

    // Modifiers
    void setPosition(int row, int col);
    void setColor(const sf::Color& blockColor);
};
#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
    int width = 50; // pixels
    int height = 50; // pixels
    int position_row = 0; // position in gameboard
    int position_column = 0; // position in gameboard
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
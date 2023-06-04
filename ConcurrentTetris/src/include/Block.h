#pragma once
#include <SFML/Graphics.hpp>
#include <atomic>

class Block
{
private:
    std::atomic<int> width = 30; // pixels
    std::atomic<int> height = 30; // pixels
    std::atomic<int> positionY = 0; // relative_position
    std::atomic<int> positionX = 0; // relative_position
    std::atomic<bool> isAlive = false; // user controlled
    sf::Color color = sf::Color::Transparent;

public:
    // Constructors
    Block(int x, int y, sf::Color blockColor);

    // Accessors
    int getWidth() const;
    int getHeight() const;
    bool getAlive();
    void setAlive(bool alive);
    sf::Color getColor() const;

    // Modifiers
    int getPositionX();
    int getPositionY();
    void setPosition(int x, int y);
};
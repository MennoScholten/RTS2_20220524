#pragma once
#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Block.h"
#include <iostream>

class Window
{
public:
    // Constructor
    Window(int width, int height, const std::string& windowName);

    // Drawing functions
    void drawGameboard(std::vector<std::vector<sf::Color>> gameboardColorVector, int blockWidth, int blockHeight);
    void drawScoreboard(int score, int time);

    // Builtin passthrough
    bool isOpen() { return window.isOpen(); }
    bool pollEvent(sf::Event& event) { return window.pollEvent(event); }
    void close() { window.close(); }
    void clear() { window.clear(); }
    void display() { window.display(); }
    bool setActive(bool active) { return window.setActive(active); }


private:
    sf::RenderWindow window;
    sf::Color GRID_COLOR;
    sf::Color SCOREBOARD_COLOR;
    float GRID_THICKNESS;
    int SCOREBOARD_HEIGHT;
    int SCOREBOARD_SPACER;
};

#pragma once

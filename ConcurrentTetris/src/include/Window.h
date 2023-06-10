#pragma once
#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Block.h"
#include <iostream>
#include "Sprite.h"

class Window
{
public:
    // Constructor
    Window(int width, int height, const std::string& windowName);

    // Drawing functions
    void drawGameboard(std::vector<std::vector<sf::Color>> gameboardColorVector, int blockWidth, int blockHeight);
    void drawScoreboard(int score1, int score2, int time);

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
    sf::Color BLOCK_OUTLINE_COLOR;
    int BLOCK_OUTLINE_THICKNESS;
    float GRID_THICKNESS;
    int SCOREBOARD_HEIGHT;
    int SCOREBOARD_SPACER;
    std::unique_ptr<CustomSprite> gamebackgroundSprite;
    std::unique_ptr<CustomSprite> ScoreBoardbackgroundSprite;
    
};

#pragma once

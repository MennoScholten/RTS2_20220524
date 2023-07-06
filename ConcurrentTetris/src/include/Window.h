#pragma once
#include <SFML/Graphics.hpp>
#include "Gameboard.h"
#include "Block.h"
#include <iostream>
#include "Sprite.h"
#include "Player.h"

class Window
{
public:
    // Constructor
    Window(int width, int height, const std::string& windowName);

    // Drawing functions
    void drawGameboard(std::vector<std::vector<Block*>> gameboardColorVector, int blockWidth, int blockHeight);
    void drawScoreboard(int score1, int score2, int time);
    void setNumberSprite(int spritenr);
    void drawSprite();
    void updateTetrominoPosition(Player* player, Gameboard* board);
    // Builtin passthrough
    bool isOpen() { return window.isOpen(); }
    bool pollEvent(sf::Event& event) { return window.pollEvent(event); }
    void close() { window.close(); }
    void clear() { window.clear(); }
    void display() { window.display(); }
    bool setActive(bool active) { return window.setActive(active); }
    void setFramerateLimit(unsigned int limit) { window.setFramerateLimit(limit); }

    
private:
    int spritenr = 0;
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
    std::unique_ptr<CustomSprite> number1 = std::make_unique<CustomSprite>("assets/sprites/number-1.png", false, 0, 0.0f, 0, 0);
    std::unique_ptr<CustomSprite> number2 = std::make_unique<CustomSprite>("assets/sprites/number-2.png", false, 0, 0.0f, 0, 0);
    std::unique_ptr<CustomSprite> number3 = std::make_unique<CustomSprite>("assets/sprites/number-3.png", false, 0, 0.0f, 0, 0);
    std::unique_ptr<CustomSprite> number4 = std::make_unique<CustomSprite>("assets/sprites/number-4.png", false, 0, 0.0f, 0, 0);
};

#pragma once

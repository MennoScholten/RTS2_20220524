#pragma once
#include <SFML/Graphics.hpp>
#include "Gameboard.h"

class Window
{
public:
    // Constructor
    Window(int width, int height, const std::string& windowName);

    // Drawing functions
    void drawGameboard(Gameboard* gameboard, Block* block_size_reference);
    void drawScoreboard(int score, int time);

    // Get - Set
    int getScoreboardSize();

    // Builtin passthrough
    bool isOpen() { return window.isOpen(); }
    bool pollEvent(sf::Event& event) { return window.pollEvent(event); }
    void close() { window.close(); }
    void clear() { window.clear(); }
    void display() { window.display(); }


private:
    sf::RenderWindow window;
    sf::Color GRID_COLOR;
    sf::Color SCOREBOARD_COLOR;
    float GRID_THICKNESS;
    int SCOREBOARD_HEIGHT;
    int SCOREBOARD_SPACER;
};

#pragma once

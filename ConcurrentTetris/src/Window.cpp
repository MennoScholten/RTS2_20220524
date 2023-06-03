#include "include/Window.h"

// Constructor
Window::Window(int width, int height, const std::string& windowName) {
    GRID_COLOR = sf::Color(50, 50, 50, 255);
    GRID_THICKNESS = .50;

    /* Scoreboard placeholder */
    SCOREBOARD_HEIGHT = 100;
    SCOREBOARD_SPACER = 1;
    SCOREBOARD_COLOR = sf::Color(10, 10, 20, 255);

    // Create the window
    window.create(sf::VideoMode(width, height + SCOREBOARD_HEIGHT), windowName, sf::Style::Close);
    window.setFramerateLimit(120);
}

void Window::drawGameboard(Gameboard* gameboard, int blockWidth, int blockHeight)
{
    for (int X = 0; X < gameboard->getSizeX(); X++) {
        for (int Y = 0; Y < gameboard->getSizeY(); Y++) {
            if (gameboard->isOccupied(X, Y)) {
                sf::RectangleShape block(sf::Vector2f(blockHeight, blockWidth));
                block.setFillColor(gameboard->getGameboard()[X][Y]->getColor());
                block.setPosition(Y * blockHeight, X * blockWidth + SCOREBOARD_HEIGHT);
                window.draw(block);
            }
            else {
                sf::RectangleShape block(sf::Vector2f(blockHeight, blockWidth));
                block.setOutlineColor(GRID_COLOR);
                block.setFillColor(sf::Color::Transparent);
                block.setOutlineThickness(GRID_THICKNESS);
                block.setPosition(Y * blockHeight, X * blockWidth + SCOREBOARD_HEIGHT);
                window.draw(block);
            }
        }
    }
}

void Window::drawScoreboard(int score, int time)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("assets/fonts/PixelOperator.ttf");

    text.setFont(font);
    text.setString("Scoreboard placeholder");
    text.setCharacterSize(32); // in pixels, not points!
    text.setFillColor(GRID_COLOR);
    text.setStyle(sf::Text::Italic | sf::Text::Underlined);
    text.setPosition(
        window.getSize().x / 2 - text.getGlobalBounds().width / 2,
        (SCOREBOARD_HEIGHT - SCOREBOARD_SPACER) / 2 - text.getGlobalBounds().height);

    sf::RectangleShape block(sf::Vector2f(window.getSize().x, SCOREBOARD_HEIGHT - SCOREBOARD_SPACER));
    block.setFillColor(SCOREBOARD_COLOR);
    block.setPosition(0, 0);
    window.draw(block);
    window.draw(text);
}

int Window::getScoreboardSize() {
    return Window::SCOREBOARD_HEIGHT;
}

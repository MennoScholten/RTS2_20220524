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
}

void Window::drawGameboard(Gameboard* gameboard, Block* Tetromino_size_reference)
{
    for (int row = 0; row < gameboard->getRows(); row++) {
        for (int column = 0; column < gameboard->getColumns(); column++) {
            if (gameboard->isOccupied(row, column)) {
                sf::RectangleShape block(sf::Vector2f(Tetromino_size_reference->getHeight(), Tetromino_size_reference->getWidth()));
                block.setFillColor(gameboard->getGameboard()[row][column]->getColor());
                block.setPosition(column * Tetromino_size_reference->getWidth(), row * Tetromino_size_reference->getHeight() + SCOREBOARD_HEIGHT);
                window.draw(block);
            }
            else {
                sf::RectangleShape block(sf::Vector2f(Tetromino_size_reference->getHeight(), Tetromino_size_reference->getWidth()));
                block.setOutlineColor(GRID_COLOR);
                block.setFillColor(sf::Color::Transparent);
                block.setOutlineThickness(GRID_THICKNESS);
                block.setPosition(column * Tetromino_size_reference->getWidth(), row * Tetromino_size_reference->getHeight() + SCOREBOARD_HEIGHT);
                window.draw(block);
            }
        }
    }
}

void Window::drawScoreboard(int score, int time)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../assets/fonts/PixelOperator.ttf");

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

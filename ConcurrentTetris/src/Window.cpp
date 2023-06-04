#include "include/Window.h"

// Constructor
Window::Window(int width, int height, const std::string& windowName)
    : GRID_COLOR(sf::Color(50, 50, 50, 255)), 
    GRID_THICKNESS(.50),
    SCOREBOARD_HEIGHT(150),
    SCOREBOARD_SPACER(10),
    SCOREBOARD_COLOR(sf::Color(10, 10, 20, 255))
{
    // Create the window
    window.create(sf::VideoMode(width, height + SCOREBOARD_HEIGHT), windowName, sf::Style::Close);
    window.setFramerateLimit(120);
}

void Window::drawGameboard(std::vector<std::vector<sf::Color>> gameboardColorVector, int blockWidth, int blockHeight) {
    for (int X = 0; X < gameboardColorVector.size(); X++) {
        for (int Y = 0; Y < gameboardColorVector[0].size(); Y++) {
            if (gameboardColorVector[X][Y] != sf::Color::Transparent) {
                sf::RectangleShape block(sf::Vector2f(blockHeight, blockWidth));
                block.setFillColor(gameboardColorVector[X][Y]);
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

void Window::drawScoreboard(int score1, int score2, int time)
{
    sf::Text mainText;
    sf::Text scoreTextP1;
    sf::Text scoreTextP2;
    sf::Text timeText;
    sf::Font font;
    font.loadFromFile("assets/fonts/PixelOperator.ttf");
    mainText.setFont(font);
    mainText.setString("Scoreboard");
    mainText.setCharacterSize(32); // in pixels, not points!
    mainText.setFillColor(GRID_COLOR);
    mainText.setStyle(sf::Text::Italic | sf::Text::Underlined);
    mainText.setPosition(
        window.getSize().x / 2 - mainText.getGlobalBounds().width / 2,
        (SCOREBOARD_SPACER) - mainText.getGlobalBounds().height);

    scoreTextP1.setFont(font);
    scoreTextP1.setString("Player1: " + std::to_string(score1));
    scoreTextP1.setCharacterSize(32); // in pixels, not points!
    scoreTextP1.setFillColor(sf::Color::Cyan);
    scoreTextP1.setStyle(sf::Text::Italic);
    scoreTextP1.setPosition(
        window.getSize().x / 2 - scoreTextP1.getGlobalBounds().width / 2,
        (SCOREBOARD_HEIGHT - SCOREBOARD_SPACER) - 3 * scoreTextP1.getGlobalBounds().height);

    scoreTextP2.setFont(font);
    scoreTextP2.setString("Player2: " + std::to_string(score2));
    scoreTextP2.setCharacterSize(32); // in pixels, not points!
    scoreTextP2.setFillColor(sf::Color::Red);
    scoreTextP2.setStyle(sf::Text::Italic);
    scoreTextP2.setPosition(
        window.getSize().x / 2 - scoreTextP2.getGlobalBounds().width / 2,
        (SCOREBOARD_HEIGHT - SCOREBOARD_SPACER) - 1.8 * scoreTextP2.getGlobalBounds().height);

    timeText.setFont(font);
    timeText.setString("Time: " + std::to_string(time));
    timeText.setCharacterSize(32); // in pixels, not points!
    timeText.setFillColor(sf::Color::White);
    timeText.setStyle(sf::Text::Italic);
    timeText.setPosition(
        window.getSize().x / 2 - timeText.getGlobalBounds().width / 2,
        (SCOREBOARD_HEIGHT - SCOREBOARD_SPACER) - 6 * timeText.getGlobalBounds().height);

    sf::RectangleShape block(sf::Vector2f(window.getSize().x, SCOREBOARD_HEIGHT - SCOREBOARD_SPACER));
    block.setFillColor(SCOREBOARD_COLOR);
    block.setPosition(0, 0);
    window.draw(block);
    window.draw(mainText);
    window.draw(scoreTextP1);
    window.draw(scoreTextP2);
    window.draw(timeText);
}

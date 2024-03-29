#include "include/Window.h"

// Constructor
Window::Window(int width, int height, const std::string& windowName)
    : GRID_COLOR(sf::Color(50, 50, 50, 255)),
    GRID_THICKNESS(.50),
    SCOREBOARD_HEIGHT(150),
    SCOREBOARD_SPACER(10),
    BLOCK_OUTLINE_COLOR(sf::Color(100, 100, 100, 255)),
    BLOCK_OUTLINE_THICKNESS(1),
    SCOREBOARD_COLOR(sf::Color(1, 4, 61, 125))
{
    // Create the window
    window.create(sf::VideoMode(width, height + SCOREBOARD_HEIGHT), windowName, sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    this->gamebackgroundSprite = std::make_unique<CustomSprite>("assets/sprites/gradient_background.png");
    this->gamebackgroundSprite->setPosition(0, 0 + this->SCOREBOARD_HEIGHT);
    this->gamebackgroundSprite->setScale(static_cast<float>(width) / 1026, static_cast<float>(height + SCOREBOARD_HEIGHT) / 1026);

    this->ScoreBoardbackgroundSprite = std::make_unique<CustomSprite>("assets/sprites/scoreboard_gradient.png");
    this->ScoreBoardbackgroundSprite->setPosition(0, 0);
    this->ScoreBoardbackgroundSprite->setScale(static_cast<float>(width) / 800, static_cast<float>(SCOREBOARD_HEIGHT) / 800);
    
    // number sprites:

    //number1->setPosition(width/2, 0);
    number1->setScale(static_cast<float>(200) / 320, static_cast<float>(200) / 320);
    //number2->setPosition(width / 2, SCOREBOARD_HEIGHT*3);
    number2->setScale(static_cast<float>(200) / 720, static_cast<float>(200) / 720);
    //number3->setPosition(width / 2, SCOREBOARD_HEIGHT*3);
    number3->setScale(static_cast<float>(200) / 2400, static_cast<float>(200) / 2400);
    //number4->setPosition(width / 2, SCOREBOARD_HEIGHT*3);
    number4->setScale(static_cast<float>(200) / 1280, static_cast<float>(200) / 1024);
}

void Window::drawGameboard(std::vector<std::vector<Block*>> gameboard, int blockWidth, int blockHeight) {
    this->gamebackgroundSprite->draw(window);
    for (int X = 0; X < gameboard.size(); X++) {
        for (int Y = 0; Y < gameboard[0].size(); Y++) {
            if (gameboard[X][Y] != nullptr) {
                sf::RectangleShape block(sf::Vector2f(blockHeight, blockWidth));
                block.setFillColor(gameboard[X][Y]->getColor());
                block.setPosition(Y * blockHeight, X * blockWidth + SCOREBOARD_HEIGHT);
                window.draw(block);
                // Add a outline
                sf::RectangleShape block_outline(sf::Vector2f(blockHeight, blockWidth));
                block_outline.setOutlineColor(BLOCK_OUTLINE_COLOR);
                block_outline.setFillColor(sf::Color::Transparent);
                block_outline.setOutlineThickness(BLOCK_OUTLINE_THICKNESS);
                block_outline.setPosition(Y * blockHeight, X * blockWidth + SCOREBOARD_HEIGHT);
                window.draw(block_outline);
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
    // this->ScoreBoardbackgroundSprite->draw(window);
    // Too colorful I think
    drawSprite();
    sf::Text mainText;
    sf::Text scoreTextP1;
    sf::Text scoreTextP2;
    sf::Text timeText;
    sf::Font font;
    font.loadFromFile("assets/fonts/PixelOperator.ttf");
    mainText.setFont(font);
    mainText.setString("Scoreboard");
    mainText.setStyle(sf::Text::Bold);
    mainText.setCharacterSize(32); // in pixels, not points!
    mainText.setFillColor(GRID_COLOR);
    mainText.setStyle(sf::Text::Italic | sf::Text::Underlined);
    mainText.setPosition(
        window.getSize().x / 2 - mainText.getGlobalBounds().width / 2,
        (SCOREBOARD_SPACER * 2) - mainText.getGlobalBounds().height);

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
        (SCOREBOARD_HEIGHT + SCOREBOARD_SPACER / 2) - 6 * timeText.getGlobalBounds().height);

    sf::RectangleShape block(sf::Vector2f(window.getSize().x, SCOREBOARD_HEIGHT));
    block.setFillColor(SCOREBOARD_COLOR);
    block.setPosition(0, 0);
    window.draw(block);
    window.draw(mainText);
    window.draw(scoreTextP1);
    window.draw(scoreTextP2);
    window.draw(timeText);
}

void Window::setNumberSprite(int spritenr) {
    this->spritenr = spritenr;
}

void Window::drawSprite() {
    if (this->spritenr == 1) {
        //std::cout << "Draw sprite nr 1" << std::endl;
        this->number1->draw(window);
    }
    else if (this->spritenr == 2) {
        //std::cout << "Draw sprite nr 2" << std::endl;
        this->number2->draw(window);
    }
    else if (this->spritenr == 3) {
        //std::cout << "Draw sprite nr 3" << std::endl;
        this->number3->draw(window);
    }
    else if (this->spritenr == 4) {
        //std::cout << "Draw sprite nr 4" << std::endl;
        this->number4->draw(window);
    }
    else {

    }
    
}

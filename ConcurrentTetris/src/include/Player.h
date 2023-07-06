#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
class Player
{
public:
    Player(const sf::Color& color, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key rotateKey, sf::Keyboard::Key dropKey);
    int getScore();
    int setScore(int score);
    sf::Keyboard::Key getMoveLeftKey();
    sf::Keyboard::Key getMoveRightKey();
    sf::Keyboard::Key getRotateKey();
    sf::Keyboard::Key getDropKey();
    void setLastPressedKey(sf::Keyboard::Key key);
    sf::Keyboard::Key getLastPressedKey();
    sf::Color getColor();
    void setActiveTetrimino(Tetromino* tetromino);
    Tetromino* getActiveTetrimino();

private:
    int score = 0;
    Tetromino* activeTetromino;
    sf::Color playerColor;
    sf::Keyboard::Key lastPressedKey;
    sf::Keyboard::Key moveLeftKey;
    sf::Keyboard::Key moveRightKey;
    sf::Keyboard::Key rotateKey;
    sf::Keyboard::Key dropKey;
};


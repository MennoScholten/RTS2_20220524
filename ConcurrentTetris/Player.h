#pragma once
#include <SFML/Graphics.hpp>
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

private:
    int score = 0;
    sf::Color playerColor;
    sf::Keyboard::Key moveLeftKey;
    sf::Keyboard::Key moveRightKey;
    sf::Keyboard::Key rotateKey;
    sf::Keyboard::Key dropKey;
};


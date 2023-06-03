#include "include/Player.h"


Player::Player(const sf::Color& color, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key rotateKey, sf::Keyboard::Key dropKey)
{
    this->activeTetromino = nullptr;
    Player::playerColor = color;
    Player::moveLeftKey = leftKey;
    Player::moveRightKey = rightKey;
    Player::rotateKey = rotateKey;
    Player::dropKey = dropKey;
}

int Player::getScore() {
    return Player::score;
}


int Player::setScore(int score)
/* Returns new score*/
{
    Player::score = score;
    return Player::score;
}

sf::Keyboard::Key Player::getMoveLeftKey() {
    return Player::moveLeftKey;
}

sf::Keyboard::Key Player::getMoveRightKey() {
    return Player::moveRightKey;
}

sf::Keyboard::Key Player::getRotateKey() {
    return Player::rotateKey;
}

sf::Keyboard::Key Player::getDropKey() {
    return Player::dropKey;
}

sf::Color Player::getColor()
{
    return this->playerColor;
}

void Player::setActiveTetrimino(Tetromino* tetromino)
{
    this->activeTetromino = tetromino;
}

Tetromino* Player::getActiveTetrimino()
{
    return this->activeTetromino;
}


#include "include/Player.h"


Player::Player(const sf::Color& color, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key rotateKey, sf::Keyboard::Key dropKey)
    : activeTetromino(nullptr),
    playerColor(color),
    moveLeftKey(leftKey),
    moveRightKey(rightKey),
    rotateKey(rotateKey),
    dropKey(dropKey)
{
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

void Player::spawnTetromino(Gameboard* board) {
    // Adds new tetromino to the specified player and checks for game over.
    Tetromino* tetromino = new Tetromino();
    sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    tetromino->createRandomTetromino(0, board->getSizeY() / 2 - 1, this->getColor());
    bool gameOver = tetromino->addToGameBoard(board);
    if (!gameOver) {
        std::cout << "Game Over!";
        return;
    }
    this->setActiveTetrimino(tetromino);
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

void Player::setLastPressedKey(sf::Keyboard::Key key) {
    this->lastPressedKey = key;
}

sf::Keyboard::Key Player::getLastPressedKey() {
    return this->lastPressedKey;
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

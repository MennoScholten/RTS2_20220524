#include "include/Sprite.h"

Sprite::Sprite(const std::string& filename, bool isAnimation, int frameCount, float frameRate, int sheetColumns, int sheetRows) :
    isAnimation(isAnimation)
{
    if (!texture.loadFromFile(filename)) {
        std::cout << "Failed to load Sprite file\n";
    }
    sprite.setTexture(texture);

    if (this->isAnimation) {
        this->frameCount = frameCount;
        this->frameRate = frameRate;
        this->sheetColumns = sheetColumns;
        this->sheetRows = sheetRows;
        this->currentFrame = 0;
        this->clock.restart();
    }
}

void Sprite::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Sprite::setScale(float scaleX, float scaleY)
{
    this->sprite.setScale(scaleX, scaleY);
}

void Sprite::draw(sf::RenderWindow& window)
{
    if (this->isAnimation) {
        this->updateAnimation();
    }
    window.draw(this->sprite);
}

void Sprite::updateAnimation() {
    if (this->isAnimation)
    {
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed >= 1.0f / this->frameRate)
        {
            this->currentFrame = (this->currentFrame + 1) % this->frameCount;
            clock.restart();
        }

        // Calculate the rectangle for the current frame
        int frameWidth = this->texture.getSize().x / this->sheetColumns;
        int frameHeight = this->texture.getSize().y / this->sheetRows;
        int currentColumn = this->currentFrame % this->sheetRows;
        int currentRow = this->currentFrame / this->sheetColumns;
        this->sprite.setTextureRect(sf::IntRect(currentColumn * frameWidth, currentRow * frameHeight, frameWidth, frameHeight));
    }
}

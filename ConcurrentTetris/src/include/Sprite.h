#include <SFML/Graphics.hpp>
#include <iostream>

class CustomSprite
{
public:
    explicit CustomSprite(const std::string& filename, bool isAnimation = false, int frameCount = 0, float frameRate = 0, int sheetColumns = 0, int sheetRows = 0);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setScale(float scaleX, float scaleY);

private:
    void updateAnimation();
    sf::Texture texture;
    sf::Sprite sprite;
    bool isAnimation;
    int frameCount;
    float frameRate;
    int sheetColumns;
    int sheetRows;
    int currentFrame;
    sf::Clock clock;
};
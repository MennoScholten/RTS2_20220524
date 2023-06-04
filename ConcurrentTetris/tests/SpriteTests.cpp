#include <iostream>
#include <gtest/gtest.h>
#include "../src/include/Block.h"
#include "../src/include/Tetromino.h"
#include "../src/include/Sprite.h"

// DISABLED_TestShowingSprite
// Test->Test Explorer->Run (must enable)

TEST(TetrisTests, DISABLED_TestShowingSprite)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Test");
    // Create a static image sprite
    CustomSprite staticSprite("../assets/sprites/demo_square.png");
    staticSprite.setPosition(100, 100);
    staticSprite.setScale(0.05, 0.05);
    // Create an animated spritesheet
    CustomSprite animatedSprite("../assets/sprites/demo_spritesheet.png", true, 60, 15, 10, 6);
    animatedSprite.setPosition(350, 0);
    animatedSprite.setScale(1, 1);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        staticSprite.draw(window);
        animatedSprite.draw(window);
        window.display();
    }
    return;
}

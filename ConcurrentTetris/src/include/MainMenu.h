#pragma once
#include <map>
#include "Player.h"
#include "sprite.h"

class MainMenu {
public:
    struct MainMenuData {
        int numberOfPlayers;
        sf::Color player1Color;
        sf::Color player2Color;
        sf::Vector2i boardDimensions;
    };
private:
    MainMenuData data;
    sf::Font fontNormal;
    sf::Font fontBold;
    sf::Vector2i windowSize;
    std::unique_ptr<CustomSprite> backgroundSprite;

public:
    MainMenu();
    MainMenuData getMainMenuData();
    bool showMainMenu();
    void drawText(sf::RenderWindow* window);
    sf::RectangleShape createButton(sf::RenderWindow* window, int sizeX, int sizeY, sf::Color color, int x, int y);
};

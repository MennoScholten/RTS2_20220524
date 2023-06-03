#include "include/MainMenu.h"

MainMenu::MainMenu() {
	this->data.boardDimensions.x = 10;
	this->data.boardDimensions.y = 20;
	this->data.numberOfPlayers = 1;
	this->data.player1Color = sf::Color::Cyan;
	this->data.player2Color = sf::Color::Red;
	this->fontNormal.loadFromFile("assets/fonts/PixelOperator.ttf");
	this->fontBold.loadFromFile("assets/fonts/PixelOperator-Bold.ttf");
	this->windowSize.x = 400;
	this->windowSize.y = 400;
}

MainMenu::MainMenuData MainMenu::getMainMenuData() {
	return this->data;
}

void MainMenu::drawText(sf::RenderWindow* window) {
	// Set up title text
	sf::Text title;
	title.setFont(this->fontBold);
	title.setString("Tetris");
	title.setCharacterSize(50);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);
	title.setPosition(this->windowSize.x / 2 - title.getGlobalBounds().width / 2, 20);
	window->draw(title);

	// Choose players
	sf::Text numberPlayers;
	numberPlayers.setFont(this->fontNormal);
	numberPlayers.setString("Number of players:");
	numberPlayers.setCharacterSize(30);
	numberPlayers.setStyle(sf::Text::Bold);
	numberPlayers.setFillColor(sf::Color::White);
	numberPlayers.setPosition(this->windowSize.x / 2 - numberPlayers.getGlobalBounds().width / 2, 90);
	window->draw(numberPlayers);

	// Gameboard size
	sf::Text boardSizeText;
	boardSizeText.setFont(this->fontNormal);
	boardSizeText.setString("Board size:");
	boardSizeText.setCharacterSize(30);
	boardSizeText.setStyle(sf::Text::Bold);
	boardSizeText.setFillColor(sf::Color::White);
	boardSizeText.setPosition(this->windowSize.x / 2 - boardSizeText.getGlobalBounds().width / 2, 180);
	window->draw(boardSizeText);
}

sf::RectangleShape MainMenu::createButton(sf::RenderWindow* window, int sizeX, int sizeY, sf::Color color, int x, int y) {
	sf::RectangleShape button(sf::Vector2f(sizeX, sizeY));
	button.setFillColor(color);
	button.setPosition(x, y);
	return button;
}


bool MainMenu::showMainMenu() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(this->windowSize.x, this->windowSize.y), "Tetris Main Menu", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Event event;

	sf::RectangleShape onePlayerButton = this->createButton(&window, 50, 30, sf::Color::Color(100, 100, 100), 130, 130);
	sf::RectangleShape twoPlayerButton = this->createButton(&window, 50, 30, sf::Color::Color(100, 100, 100), 220, 130);
	sf::RectangleShape playButton = this->createButton(&window, 200, 60, sf::Color::Color(100, 100, 100), 100, 300);
	sf::RectangleShape boardHeightInput = this->createButton(&window, 80, 40, sf::Color::White, 110, 220);
	sf::RectangleShape boardWidthInput = this->createButton(&window, 80, 40, sf::Color::White, 210, 220);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				if (onePlayerButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    std::cout << "1 Player selected." << std::endl;
					this->data.numberOfPlayers = 1;
                }
                else if (twoPlayerButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    std::cout << "2 Players selected." << std::endl;
					this->data.numberOfPlayers = 2;
                }
				else if (playButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					std::cout << "Play!" << std::endl;
					return true;
				}
			}
        }
		window.clear();
		window.draw(onePlayerButton);
		window.draw(twoPlayerButton);
		window.draw(playButton);
		window.draw(boardHeightInput);
		window.draw(boardWidthInput);
		this->drawText(&window);
		window.display();
    }
}

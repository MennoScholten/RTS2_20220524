#include <SFML/Graphics.hpp>
#include "Gameboard.h"

int main()
{
	int width = 10;
	int height = 8;
	Gameboard gameboard(width, height);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Not Tetris");
	sf::Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}
	}

	return 0;
}
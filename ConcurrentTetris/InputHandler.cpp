#include "InputHandler.h"
#include <set>

InputHandler::InputHandler() {
    
}

void InputHandler::processInput(std::vector<Player*>& players, sf::Event event) {
    static std::set<sf::Keyboard::Key> pressedKeys;

    if (event.type == sf::Event::KeyPressed) {
        pressedKeys.insert(event.key.code);

        for (auto player : players) {
            if (pressedKeys.count(player->getMoveLeftKey())) {
                std::cout << "Move left " << player << "\n";
            }
            if (pressedKeys.count(player->getMoveRightKey())) {
                std::cout << "Move right " << player << "\n";
            }
            if (pressedKeys.count(player->getRotateKey())) {
                std::cout << "Rotate " << player << "\n";
            }
            if (pressedKeys.count(player->getDropKey())) {
                std::cout << "Drop " << player << "\n";
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        pressedKeys.erase(event.key.code);
    }
}
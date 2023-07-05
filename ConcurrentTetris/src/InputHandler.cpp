#include "include/InputHandler.h"
#include <set>

InputHandler::InputHandler() {
    
}

void InputHandler::processInput(Player* player, Gameboard* gameboard) {

    if (sf::Keyboard::isKeyPressed(player->getMoveLeftKey()))
    {
        std::cout << "Move left " << player << "\n";
        if (player->getActiveTetrimino() != nullptr && player->getMoveLeftKey() != player->getLastPressedKey()) {
            player->getActiveTetrimino()->moveLeft(gameboard);
        }
        player->setLastPressedKey(player->getMoveLeftKey());
    }

    else if (sf::Keyboard::isKeyPressed(player->getMoveRightKey()))
    {
        std::cout << "Move right " << player << "\n";
        if (player->getActiveTetrimino() != nullptr && player->getMoveRightKey() != player->getLastPressedKey()) {
            player->getActiveTetrimino()->moveRight(gameboard);
        } 
        player->setLastPressedKey(player->getMoveRightKey());
    }

    else if (sf::Keyboard::isKeyPressed(player->getRotateKey()))
    {
        std::cout << "Rotate " << player << "\n";
        if (player->getActiveTetrimino() != nullptr && player->getRotateKey() != player->getLastPressedKey()) {
            player->getActiveTetrimino()->rotateClockwise(gameboard);
        } 
        player->setLastPressedKey(player->getRotateKey());
    }

    else if (sf::Keyboard::isKeyPressed(player->getDropKey()))
    {
        std::cout << "Drop " << player << "\n";
        if (player->getActiveTetrimino() != nullptr && player->getDropKey() != player->getLastPressedKey()) {
            player->getActiveTetrimino()->moveDrop(gameboard);
        }
        player->setLastPressedKey(player->getRotateKey());
    }
    else {
        player->setLastPressedKey(sf::Keyboard::Unknown);
    }
}

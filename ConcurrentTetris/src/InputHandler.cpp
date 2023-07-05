#include "include/InputHandler.h"
#include <set>

InputHandler::InputHandler() {
    
}
bool upArrowPressed = true;
bool upArrowReleased;

char InputHandler::pollingServer()
{
#ifdef _WIN32
    if (_kbhit())
    {
        return _getch();
    }
#else
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    int character = 0;
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) > 0)
    {
        character = getchar();
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    if (character != 0)
    {
        return character;
    }
#endif
    return '\0';
}

void InputHandler::processInput(const std::vector<Player*>& players, Gameboard* gameboard, sf::Event event) {
    static std::set<sf::Keyboard::Key> pressedKeys;

    if (event.type == sf::Event::KeyPressed) {
        pressedKeys.insert(event.key.code);

        for (auto player : players) {
            if (pressedKeys.count(player->getMoveLeftKey())) {
                std::cout << "Move left " << player << "\n";
                if (player->getActiveTetrimino() != nullptr) player->getActiveTetrimino()->moveLeft(gameboard);
            }
            if (pressedKeys.count(player->getMoveRightKey())) {
                std::cout << "Move right " << player << "\n";
                if (player->getActiveTetrimino() != nullptr) player->getActiveTetrimino()->moveRight(gameboard);
            }
            if (pressedKeys.count(player->getRotateKey())) {
                std::cout << "Rotate " << player << "\n";
                if (player->getActiveTetrimino() != nullptr) player->getActiveTetrimino()->rotateClockwise(gameboard);
            }
            if (pressedKeys.count(player->getDropKey())) {
                if (player->getActiveTetrimino() != nullptr) player->getActiveTetrimino()->moveDrop(gameboard);
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        pressedKeys.erase(event.key.code);
    }
}

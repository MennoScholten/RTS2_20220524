#pragma once
#include <SFML/Window/Event.hpp>
#include <thread> // It seems input handling is not recommended to be threaded
#include <atomic>
#include <vector>
#include "Player.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>  // Required for Windows
#else
#include <unistd.h> // Required for Linux
#include <termios.h>
#endif

class InputHandler {
public:
    InputHandler();
    char pollingServer();
    void processInput(const std::vector<Player*>& players, Gameboard* gameboard, sf::Event event);

private:
};


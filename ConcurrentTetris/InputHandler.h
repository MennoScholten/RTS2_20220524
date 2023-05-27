#pragma once
#include <SFML/Window/Event.hpp>
#include <thread> // It seems input handling is not recommended to be threaded
#include <atomic>
#include <vector>
#include "Player.h"
#include <iostream>

class InputHandler {
public:
    InputHandler();
    void processInput(std::vector<Player*>& players, sf::Event event);

private:
};


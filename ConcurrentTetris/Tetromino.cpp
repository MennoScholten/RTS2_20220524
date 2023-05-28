#include "Tetromino.h"
#include <iostream>
Tetromino::Tetromino(int x, int y, sf::Color color, Gameboard* gameboard) {
}

void Tetromino::addToGameBoard(Gameboard* gameboard) {
    for (Block* block : this->blocks) {
        gameboard->addBlock(block->getPositionX(), block->getPositionY(), block);
    }
}

Tetromino Tetromino::blockI(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y, color);
    Block* block2 = new Block(x + 1, y, color);
    Block* block3 = new Block(x + 2, y, color);
    Block* block4 = new Block(x + 3, y, color);
    tetromino.pivotPointOffset.x = 0;
    tetromino.pivotPointOffset.y = 0;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockL(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y, color);
    Block* block2 = new Block(x, y + 1, color);
    Block* block3 = new Block(x + 1, y + 1, color);
    Block* block4 = new Block(x + 2, y + 1, color);
    tetromino.pivotPointOffset.x = 1;
    tetromino.pivotPointOffset.y = 1;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockJ(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 2, y + 1, color);
    Block* block4 = new Block(x + 2, y + 0, color);
    tetromino.pivotPointOffset.x = 1;
    tetromino.pivotPointOffset.y = 1;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockZ(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 1, y, color);
    Block* block4 = new Block(x + 2, y, color);
    tetromino.pivotPointOffset.x = 1;
    tetromino.pivotPointOffset.y = 1;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockS(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x + 2, y + 2, color);
    Block* block2 = new Block(x + 1, y + 2, color);
    Block* block3 = new Block(x + 1, y + 1, color);
    Block* block4 = new Block(x, y + 1, color);
    tetromino.pivotPointOffset.x = 1;
    tetromino.pivotPointOffset.y = 1;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockT(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 1, y , color);
    Block* block4 = new Block(x + 2, y + 1, color);
    tetromino.pivotPointOffset.x = 1;
    tetromino.pivotPointOffset.y = 1;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}

Tetromino Tetromino::blockO(int x, int y, sf::Color color, Gameboard* gameboard) {
    Tetromino tetromino(x, y, color, gameboard);
    Block* block1 = new Block(x, y, color);
    Block* block2 = new Block(x + 1, y, color);
    Block* block3 = new Block(x, y + 1, color);
    Block* block4 = new Block(x + 1, y + 1, color);
    tetromino.pivotPointOffset.x = 0;
    tetromino.pivotPointOffset.y = 0;
    tetromino.blocks.push_back(block1);
    tetromino.blocks.push_back(block2);
    tetromino.blocks.push_back(block3);
    tetromino.blocks.push_back(block4);
    tetromino.setGridPosition(x, y);
    tetromino.addToGameBoard(gameboard);
    return tetromino;
}


sf::Vector2i Tetromino::getPivotPoint() {
    this->pivotPoint.x = this->gridPosition.x + this->pivotPointOffset.x;
    this->pivotPoint.y = this->gridPosition.y + this->pivotPointOffset.y;
    return this->pivotPoint;
}

void Tetromino::setGridPosition(int x, int y) {
    this->gridPosition.x = x;
    this->gridPosition.y = y;
}

sf::Vector2i Tetromino::getGridPosition() {
    return this->gridPosition;
}

void Tetromino::rotateClockwise(Gameboard* board) {
    /* Something cross between SRS and TGM rotation system 
    https://tetris.wiki/Arika_Rotation_System
    https://tetris.fandom.com/wiki/TGM_Rotation */

    // Store the current blocks' positions for potential rollback when checking for collisions
    std::vector<std::pair<int, int>> oldPositions;
    for (auto block : blocks) {
        oldPositions.push_back(std::make_pair(block->getPositionX(), block->getPositionY()));
    }
    this->getPivotPoint(); // Update pivot
    // Can't rotate (O block)
    if (this->pivotPointOffset.x == 0 && this->pivotPointOffset.y == 0) {
        return;
    }
    for (auto block : blocks) {
        int relativeX = block->getPositionX() - this->pivotPoint.x;
        int relativeY = block->getPositionY() - this->pivotPoint.y;
        int newX = -relativeY;
        int newY = relativeX;
        std::cout << "newX: " << newX << "\n";
        std::cout << "newY: " << newY << std::endl;
        // Should check for collisions here
        board->moveBlock(block, this->pivotPoint.x + newX, this->pivotPoint.y + newY);
        block->setPosition(this->pivotPoint.x + newX, this->pivotPoint.y + newY);
    }
}

void Tetromino::moveRight(Gameboard* board) {

    // Store the current blocks' positions for potential rollback when checking for collisions
    std::vector<std::pair<int, int>> oldPositions;
    for (auto block : blocks) {
        oldPositions.push_back(std::make_pair(block->getPositionX(), block->getPositionY()));
    }
    for (auto block : blocks) {
        int relativeX = block->getPositionX();
        int relativeY = block->getPositionY();
        int newX = relativeX + 1;
        int newY = relativeY;
        std::cout << "newX: " << newX << "\n";
        std::cout << "newY: " << newY << std::endl;

        // Should check for collisions here
        board->moveBlock(block, newX, newY);
        block->setPosition(newX, newY);
    }
    // Update block grid position
    this->setGridPosition(this->gridPosition.x + 1, this->gridPosition.y + 0);
}

void Tetromino::moveLeft(Gameboard* board) {

    // Store the current blocks' positions for potential rollback when checking for collisions
    std::vector<std::pair<int, int>> oldPositions;
    for (auto block : blocks) {
        oldPositions.push_back(std::make_pair(block->getPositionX(), block->getPositionY()));
    }

    for (auto block : blocks) {
        int relativeX = block->getPositionX();
        int relativeY = block->getPositionY();
        int newX = relativeX - 1;
        int newY = relativeY;
        std::cout << "newX: " << newX << "\n";
        std::cout << "newY: " << newY << std::endl;

        // Should check for collisions here
        board->moveBlock(block, newX, newY);
        block->setPosition(newX, newY);
        
    }
    this->setGridPosition(this->gridPosition.x - 1, this->gridPosition.y + 0);
}
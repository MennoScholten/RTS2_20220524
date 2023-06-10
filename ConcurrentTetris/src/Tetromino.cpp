#include "include/Tetromino.h"
#include <iostream>
Tetromino::Tetromino() {
    std::fill(blocks.begin(), blocks.end(), nullptr);
}

void Tetromino::createRandomTetromino(int x, int y, sf::Color color) {
    int selection;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 6);
    selection = dis(gen);

    switch (selection) {
    case 0:
        blockI(x, y, color);
        break;
    case 1:
        blockL(x, y, color);
        break;
    case 2:
        blockO(x, y, color);
        break;
    case 3:
        blockZ(x, y, color);
        break;
    case 4:
        blockS(x, y, color);
        break;
    case 5:
        blockT(x, y, color);
        break;
    case 6:
        blockJ(x, y, color);
        break;
    default:
        break;
    }
}

bool Tetromino::addToGameBoard(Gameboard* gameboard) {
    /**
    * Add tetromino object to gameboard
    * Check for collision before. If collision is detected, game is over
    */
    if (this->checkIfMoveIsValid(gameboard, 0, 0)) {
        for (Block* block : this->blocks) {
            gameboard->addBlock(block->getPositionX(), block->getPositionY(), block);
        }
        return true;
    }
    return false;
}

void Tetromino::blockI(int x, int y, sf::Color color) {
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 2, y + 1, color);
    Block* block4 = new Block(x + 3, y + 1, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockL(int x, int y, sf::Color color) {
    Block* block1 = new Block(x, y, color);
    Block* block2 = new Block(x, y + 1, color);
    Block* block3 = new Block(x + 1, y + 1, color);
    Block* block4 = new Block(x + 2, y + 1, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockJ(int x, int y, sf::Color color) {
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 2, y + 1, color);
    Block* block4 = new Block(x + 2, y + 0, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockZ(int x, int y, sf::Color color) {
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 1, y, color);
    Block* block4 = new Block(x + 2, y, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockS(int x, int y, sf::Color color) {
    Block* block1 = new Block(x + 2, y + 2, color);
    Block* block2 = new Block(x + 1, y + 2, color);
    Block* block3 = new Block(x + 1, y + 1, color);
    Block* block4 = new Block(x, y + 1, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockT(int x, int y, sf::Color color) {
    
    Block* block1 = new Block(x, y + 1, color);
    Block* block2 = new Block(x + 1, y + 1, color);
    Block* block3 = new Block(x + 1, y , color);
    Block* block4 = new Block(x + 2, y + 1, color);
    this->pivotPointOffset.x = 1;
    this->pivotPointOffset.y = 1;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
}

void Tetromino::blockO(int x, int y, sf::Color color) {
    Block* block1 = new Block(x, y, color);
    Block* block2 = new Block(x + 1, y, color);
    Block* block3 = new Block(x, y + 1, color);
    Block* block4 = new Block(x + 1, y + 1, color);
    this->pivotPointOffset.x = 0;
    this->pivotPointOffset.y = 0;
    this->blocks.push_back(block1);
    this->blocks.push_back(block2);
    this->blocks.push_back(block3);
    this->blocks.push_back(block4);
    this->setGridPosition(x, y);
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

void Tetromino::rotateClockwise(Gameboard* board) {

    this->getPivotPoint(); // Update pivot

    // Can't rotate (O block)
    if (this->pivotPointOffset.x == 0 && this->pivotPointOffset.y == 0) {
        return;
    }
    if (this->checkIfMoveIsValid(board, 0, 0, true)) {
        for (auto block : blocks) {
            int relativeX = block->getPositionX() - this->pivotPoint.x;
            int relativeY = block->getPositionY() - this->pivotPoint.y;
            int newX = this->pivotPoint.x + relativeY;
            int newY = this->pivotPoint.y - relativeX;
            board->moveBlock(block, newX, newY);
        }
        return;
    }
    // wallkick
    else {
        if (this->checkIfMoveIsValid(board, 0, 2, false)) {
            //std::cout << "move +2 valid!" << std::endl;
            moveRight(board);
            moveRight(board);

            if (this->checkIfMoveIsValid(board, 0, 0, true)) {
                for (auto block : blocks) {
                    int relativeX = block->getPositionX() - this->pivotPoint.x;
                    int relativeY = block->getPositionY() - this->pivotPoint.y;
                    int newX = this->pivotPoint.x + relativeY;
                    int newY = this->pivotPoint.y - relativeX;
                    board->moveBlock(block, newX, newY);
                }
            }
            return;
        }
        else if (this->checkIfMoveIsValid(board, 0, -2, false)) {
            //std::cout << "move -2 valid!" << std::endl;
            moveLeft(board);
            moveLeft(board);
            if (this->checkIfMoveIsValid(board, 0, 0, true)) {
                for (auto block : blocks) {
                    int relativeX = block->getPositionX() - this->pivotPoint.x;
                    int relativeY = block->getPositionY() - this->pivotPoint.y;
                    int newX = this->pivotPoint.x + relativeY;
                    int newY = this->pivotPoint.y - relativeX;
                    board->moveBlock(block, newX, newY);
                }
            }
            return;
        }
    }

}

void Tetromino::moveRight(Gameboard* board) {
    if (this->checkIfMoveIsValid(board, 0, 1)) {
        for (auto block : blocks) {
            int newX = block->getPositionX();
            int newY = block->getPositionY() + 1;
            board->moveBlock(block, newX, newY);
        }
        this->setGridPosition(this->gridPosition.x, this->gridPosition.y + 1);
    }
}

void Tetromino::moveLeft(Gameboard* board) {
    if (this->checkIfMoveIsValid(board, 0, -1)) {
        for (auto block : blocks) {
            int newX = block->getPositionX();
            int newY = block->getPositionY() - 1;
            board->moveBlock(block, newX, newY);
        }
        this->setGridPosition(this->gridPosition.x, this->gridPosition.y - 1);
    }
}

bool Tetromino::moveDown(Gameboard* board) {
    /**
    * Returns true if move was legal, false if block can not move down any more.
    */
    if (this->checkIfMoveIsValid(board, 1, 0)) {
        for (auto block : blocks) {
            int newX = block->getPositionX() + 1;
            int newY = block->getPositionY();
            board->moveBlock(block, newX, newY);
        }
        this->setGridPosition(this->gridPosition.x + 1, this->gridPosition.y);
        return true;
    }
    return false;
}

void Tetromino::moveDrop(Gameboard* board) {
    // Validate that move is valid
    while (this->checkIfMoveIsValid(board, 1, 0)) {
        for (auto block : blocks) {
            int newX = block->getPositionX() + 1;
            int newY = block->getPositionY();
            board->moveBlock(block, newX, newY);
        }
        this->setGridPosition(this->gridPosition.x + 1, this->gridPosition.y);
    }
}

bool Tetromino::checkIfMoveIsValid(Gameboard* board, int tetrominoNewX, int tetrominoNewY, bool rotation) {
    std::vector<bool> isValid;
    int newX, newY;
    for (auto block : this->blocks) {
        if (rotation) {
            int relativeX = block->getPositionX() - this->pivotPoint.x;
            int relativeY = block->getPositionY() - this->pivotPoint.y;
            newX = this->pivotPoint.x + relativeY;
            newY = this->pivotPoint.y - relativeX;
        }
        else {
            newX = block->getPositionX() + tetrominoNewX;
            newY = block->getPositionY() + tetrominoNewY;
        }
        // Check for collisions
        isValid.push_back(board->checkCollision(newX, newY));
    }
    return !std::any_of(isValid.begin(), isValid.end(), [](bool status) { return status; });
}

void Tetromino::updatePosition(Gameboard* board) {
    /**
    * Other player can overwrite the blocks
    * They would reappear next tick, this will update them back immediately.
    */
    if (this->checkIfMoveIsValid(board, 0, 0)) {
        for (auto block : blocks) {
            int newX = block->getPositionX();
            int newY = block->getPositionY();
            board->moveBlock(block, newX, newY);
        }
        this->setGridPosition(this->gridPosition.x, this->gridPosition.y);
    }
}

void Tetromino::freezeToBoard(Gameboard* board) {
    /**
    * Converts block to a static block inherited by gameboard
    * Deletes the blocks owned by this class
    */
    for (Block* block : blocks) {
        board->createLockedBlock(block);
        delete block;
    }
}

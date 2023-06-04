#include <iostream>
#include <gtest/gtest.h>
#include "../src/include/Block.h"
#include "../src/include/Gameboard.h"

TEST(TetrisTests, TestCreatingGameboard)
{
    // Columns, Rows
    Gameboard board(10, 10);
    ASSERT_EQ(board.getGameboard().size(), 10);
    ASSERT_EQ(board.getGameboard()[0].size(), 10);
    Gameboard board2(12, 8);
    ASSERT_EQ(board2.getGameboard().size(), 12);
    ASSERT_EQ(board2.getGameboard()[0].size(), 8);
}

TEST(TetrisTests, TestAddingTilesToGameboard)
{
    Gameboard board(12, 8);
    Block block(3, 6, sf::Color::Blue);
    Block block2(4, 7, sf::Color::Red);
    board.addBlock(block.getPositionX(), block.getPositionY(), &block);
    board.addBlock(block2.getPositionX(), block2.getPositionY(), &block2);
    ASSERT_EQ(board.getGameboard()[block.getPositionX()][block.getPositionY()], &block);
    ASSERT_EQ(board.getGameboard()[block2.getPositionX()][block2.getPositionY()], &block2);
}

TEST(TetrisTests, TestGameboardCollision)
{
    Gameboard board(12, 8);
    Block block(3, 6, sf::Color::Blue);
    Block block2(4, 7, sf::Color::Red);
    block.setAlive(false);
    block2.setAlive(false);
    board.addBlock(block.getPositionX(), block.getPositionY(), &block);
    board.addBlock(block2.getPositionX(), block2.getPositionY(), &block2);
    ASSERT_TRUE(board.checkCollision(block.getPositionX(), block.getPositionY()));
}

TEST(TetrisTests, TestGameboardMoveBlock)
{
    Gameboard board(12, 8);
    Block block(3, 6, sf::Color::Blue);
    Block block2(4, 7, sf::Color::Red);
    block.setAlive(false);
    block2.setAlive(false);
    board.addBlock(block.getPositionX(), block.getPositionY(), &block);
    board.addBlock(block2.getPositionX(), block2.getPositionY(), &block2);
    board.moveBlock(&block, 11, 0);
    board.moveBlock(&block2, 2, 7);
    ASSERT_EQ(board.getGameboard()[block.getPositionX()][block.getPositionY()], &block);
    ASSERT_EQ(board.getGameboard()[block2.getPositionX()][block2.getPositionY()], &block2);
}

TEST(TetrisTests, TestClearingRows)
{
    int BOARD_HEIGHT_X = 5;
    int BOARD_WIDTH_Y = 8;
    Gameboard board(BOARD_HEIGHT_X, BOARD_WIDTH_Y);
    for (int i = 0; i < BOARD_WIDTH_Y; i++) {
        // Fill last 2 rows
        Block* block = new Block(0, 0, sf::Color::Blue);
        Block* block2 = new Block(0, 0, sf::Color::Blue);
        block->setAlive(false);
        block2->setAlive(false);
        board.addBlock(BOARD_HEIGHT_X - 1, i, block);
        board.addBlock(BOARD_HEIGHT_X - 2, i, block2);
    }
    int cleared_rows = board.checkFilledRows();
    ASSERT_EQ(cleared_rows, 2);
    ASSERT_EQ(board.getGameboard()[BOARD_HEIGHT_X-1][0], nullptr);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <iostream>
#include <gtest/gtest.h>
#include "../src/include/Block.h"
#include "../src/include/Tetromino.h"

TEST(TetrisTests, TestCreatingTetromino)
{
    Tetromino* tetromino = new Tetromino();
    tetromino->blockI(0, 0, sf::Color::Red);
    ASSERT_EQ(tetromino->getPivotPoint().x, 1);
}
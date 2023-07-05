cmake_minimum_required(VERSION 3.12)
project(TetrisTests)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Source files
set(SOURCES
    ../src/Block.cpp
    ../src/Gameboard.cpp
    ../src/InputHandler.cpp
    ../src/Player.cpp
    ../src/Tetromino.cpp
    ../src/Window.cpp
    ../src/Sprite.cpp
)

# Add the executable for all tests
add_executable(AllTests 
    "GameboardTests.cpp" 
    "TetrominoTests.cpp" 
    "SpriteTests.cpp" 
    ${SOURCES})

# Game assets
add_custom_target(CopyTestAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets directory"
    VERBATIM
)

# Game assets
add_dependencies(AllTests CopyTestAssets)

# Link
target_link_libraries(AllTests PRIVATE GTest::GTest sfml-system sfml-audio sfml-window sfml-graphics)

# Add a test for running all the tests
add_test(NAME RunTests COMMAND AllTests)

# Add the separate executable for WCET.cpp
add_executable(WCET "WCET.cpp" ${SOURCES})
add_dependencies(WCET CopyTestAssets)
target_link_libraries(WCET PRIVATE GTest::GTest sfml-system sfml-audio sfml-window sfml-graphics)
add_test(NAME RunWCET COMMAND WCET)

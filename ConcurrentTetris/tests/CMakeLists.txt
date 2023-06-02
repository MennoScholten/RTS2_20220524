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
)

# Add the executable
add_executable(AllTests 
"GameboardTests.cpp" 
"TetrominoTests.cpp" 
${SOURCES})

# Game assets
file(COPY ../assets DESTINATION ${CMAKE_BINARY_DIR})

# Link
target_link_libraries(AllTests PRIVATE GTest::GTest sfml-system sfml-audio sfml-main sfml-window sfml-graphics gdi32 opengl32)

# Add a test for running all the tests
add_test(NAME RunTests COMMAND AllTests)

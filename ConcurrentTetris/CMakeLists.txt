cmake_minimum_required(VERSION 3.12)
project(ConcurrentTetris)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)

# set(SFML_DIR "C:/SFML-2.5.1-VS/lib/cmake/SFML") # Visual Studio
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML") # VSCode

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add your source files
set(SOURCES
    src/main.cpp
    src/Block.cpp
    src/Gameboard.cpp
    src/InputHandler.cpp
    src/Player.cpp
    src/Tetromino.cpp
    src/Window.cpp
)

# Add the executable
add_executable(ConcurrentTetromino ${SOURCES})

# Link SFML libraries
target_link_libraries(ConcurrentTetromino PRIVATE sfml-system sfml-window sfml-graphics)

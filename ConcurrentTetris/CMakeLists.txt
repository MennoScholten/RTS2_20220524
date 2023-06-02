cmake_minimum_required(VERSION 3.12)
project(ConcurrentTetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

# SFML library
if(UNIX)
elseif(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
endif()
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Add tests
add_subdirectory(tests)

# Add your source files
set(SOURCES
    src/Main.cpp
    src/Block.cpp
    src/Gameboard.cpp
    src/InputHandler.cpp
    src/Player.cpp
    src/Tetromino.cpp
    src/Window.cpp
)

# Add the executable
add_executable(ConcurrentTetromino ${SOURCES})

# Game assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Link SFML libraries
target_link_libraries(ConcurrentTetromino PUBLIC sfml-system sfml-audio sfml-main sfml-window sfml-graphics gdi32 opengl32)

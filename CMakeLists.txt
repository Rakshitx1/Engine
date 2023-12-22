cmake_minimum_required(VERSION 3.0.0)

project(PhysicsEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Find SDL2
find_package(SDL2 REQUIRED)

# Specify the path to SDL2_ttf (adjust the path accordingly)
set(SDL2TTF_DIR "/usr/include/SDL2")

# Add SDL2_ttf include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_DIR})

# Add SDL2_ttf library
find_library(SDL2TTF_LIBRARY SDL2_ttf)

set(SOURCES 
    src/main.cpp
)

add_executable(PhysicsEngine ${SOURCES})

# Link against SDL2 and SDL2_ttf libraries
target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})

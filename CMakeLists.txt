cmake_minimum_required(VERSION 3.10)

project(PhysicsEngine)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Set source files
set(SOURCES src/main.cpp)

# Create the executable
add_executable(PhysicsEngine ${SOURCES})

# Link against SDL2 library
target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES})

cmake_minimum_required(VERSION 3.0.0)

project(PhysicsEngine VERSION 0.1.0 LANGUAGES CXX)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Set source files
set(SOURCES 
    src/main.cpp
)

# Create the executable
add_executable(PhysicsEngine ${SOURCES})

# Include SDL2 headers
target_include_directories(PhysicsEngine PRIVATE ${SDL2_INCLUDE_DIRS})

# Link against SDL2 library
target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES})

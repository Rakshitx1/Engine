cmake_minimum_required(VERSION 3.0.0)

project(PhysicsEngine VERSION 0.1.0 LANGUAGES CXX)

find_package(SDL2 REQUIRED)

set(SOURCES 
    src/main.cpp
)

add_executable(PhysicsEngine ${SOURCES})

target_include_directories(PhysicsEngine PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES})

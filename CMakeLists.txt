cmake_minimum_required(VERSION 3.0.0)

project(PhysicsEngine VERSION 0.1.0 LANGUAGES CXX)

# Set the build type to Debug by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

# Find SDL2
find_package(SDL2 REQUIRED)

# List your source files
set(SOURCES 
    src/main.cpp
    src/Circle.cpp
    include/Circle.hpp
)

# Create an executable
add_executable(PhysicsEngine ${SOURCES})

# Include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Include directory
target_include_directories(PhysicsEngine PRIVATE include)

# Link the executable with SDL2 libraries
target_link_libraries(PhysicsEngine PRIVATE ${SDL2_LIBRARIES})

# Set compiler flags for Debug
# target_compile_options(PhysicsEngine PRIVATE "$<$<CONFIG:DEBUG>: -O0 -g>")

# Set compiler flags for Release
target_compile_options(PhysicsEngine PRIVATE "$<$<CONFIG:RELEASE>: -O3>")

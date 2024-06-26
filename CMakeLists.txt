cmake_minimum_required(VERSION 3.5.0)

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

# Include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# List your source files
set(SOURCES 
    src/main.cpp
)

# Create an executable
add_executable(PhysicsEngine ${SOURCES})

# Link the executable with SDL2 libraries
target_link_libraries(PhysicsEngine PRIVATE ${SDL2_LIBRARIES})

# Set compiler flags
target_compile_options(PhysicsEngine PRIVATE -m64)

# Set compiler flags for Debug
target_compile_options(PhysicsEngine PRIVATE $<$<CONFIG:DEBUG>: -O0 -g -Wall>)

# Set compiler flags for Release
target_compile_options(PhysicsEngine PRIVATE $<$<CONFIG:RELEASE>: -O3>)

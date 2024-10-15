cmake_minimum_required(VERSION 3.10)
project(QR-Code-Gen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Specify the location of SDL2 headers and libraries manually
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/SDL2")
set(SDL2_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib")

# Check if SDL2 header files exist
if (NOT EXISTS "${SDL2_INCLUDE_DIR}/SDL.h")
    message(FATAL_ERROR "SDL2 header files not found in the specified include directory!")
else()
    message(STATUS "SDL2 headers found at ${SDL2_INCLUDE_DIR}")
endif()

# Check if SDL2 library files exist
if (NOT EXISTS "${SDL2_LIBRARY_DIR}/libSDL2.a" AND NOT EXISTS "${SDL2_LIBRARY_DIR}/SDL2.dll")
    message(FATAL_ERROR "SDL2 library files not found in the specified library directory!")
else()
    message(STATUS "SDL2 libraries found at ${SDL2_LIBRARY_DIR}")
endif()

# Add your project include directory (e.g., where screen.hpp, etc. are located)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the SDL2 include directory manually
include_directories(${SDL2_INCLUDE_DIR})

# Manually add the library directory
link_directories(${SDL2_LIBRARY_DIR})

# Gather all the source files
file(GLOB SOURCES "src/*.cpp")

# Define the executable for your project
add_executable(QR-Code-Gen ${SOURCES})

# Link SDL2 and other required libraries
target_include_directories(QR-Code-Gen PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories(QR-Code-Gen PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(QR-Code-Gen mingw32 SDL2main SDL2)

# For Windows, you might need to specify SDL2.dll if linking dynamically
# For static linking, remove the SDL2.dll dependency and rely on the static lib (libSDL2.a)
if (WIN32)
    target_link_libraries(QR-Code-Gen SDL2)
endif()

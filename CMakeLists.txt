cmake_minimum_required(VERSION 3.10)
project(QRCodeGen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/SDL2)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})

target_include_directories(main PRIVATE include include/SDL2)
target_link_libraries(main mingw32 SDL2main SDL2)
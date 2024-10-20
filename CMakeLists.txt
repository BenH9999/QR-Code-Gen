# Specify the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(QR_Code_Gen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check the operating system
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows-specific logic

    # Define the function to download and set up SDL2
    function(download_sdl2)
        message(STATUS "SDL2 not found, downloading...")

        # Set the download URL and target location for the SDL2 files
        set(SDL2_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-2.30.8/SDL2-devel-2.30.8-mingw.zip")
        set(SDL2_DOWNLOAD_FILE "${CMAKE_BINARY_DIR}/SDL2.zip")
        set(SDL2_EXTRACT_DIR "${CMAKE_BINARY_DIR}/SDL2")

        # Download SDL2 archive
        message(STATUS "Downloading SDL2 from ${SDL2_DOWNLOAD_URL}...")
        file(DOWNLOAD ${SDL2_DOWNLOAD_URL} ${SDL2_DOWNLOAD_FILE} SHOW_PROGRESS)

        # Unzip the SDL2 package
        message(STATUS "Extracting SDL2...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz ${SDL2_DOWNLOAD_FILE} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

        # Find the extracted folder (with version number)
        file(GLOB SDL2_VERSIONED_DIR "${CMAKE_BINARY_DIR}/SDL2-*")

        # Check if the extracted folder exists
        if (NOT SDL2_VERSIONED_DIR)
            message(FATAL_ERROR "Failed to find the extracted SDL2 directory!")
        endif()

        # Get the first element in the folder list (folder with version number)
        list(GET SDL2_VERSIONED_DIR 0 SDL2_EXTRACTED_FOLDER)

        # Show the found folder for debugging
        message(STATUS "Found SDL2 extracted folder: ${SDL2_EXTRACTED_FOLDER}")

        # Set paths for SDL2 include, lib, and bin directories
        set(SDL2_INCLUDE_DIR "${SDL2_EXTRACTED_FOLDER}/x86_64-w64-mingw32/include")
        set(SDL2_LIB_DIR "${SDL2_EXTRACTED_FOLDER}/x86_64-w64-mingw32/lib")
        set(SDL2_BIN_DIR "${SDL2_EXTRACTED_FOLDER}/x86_64-w64-mingw32/bin") # DLL directory

        # Ensure the header files exist
        if (NOT EXISTS "${SDL2_INCLUDE_DIR}")
            message(FATAL_ERROR "SDL2 header files not found in the extracted directory!")
        endif()

        # Ensure the library files exist
        if (NOT EXISTS "${SDL2_LIB_DIR}")
            message(FATAL_ERROR "SDL2 library files not found in the extracted directory!")
        endif()

        # Ensure the DLL exists
        if (NOT EXISTS "${SDL2_BIN_DIR}/SDL2.dll")
            message(FATAL_ERROR "SDL2.dll not found in the extracted directory!")
        endif()

        # Copy include files to the correct location
        message(STATUS "Copying SDL2 headers to ${CMAKE_SOURCE_DIR}/include/SDL2")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${SDL2_INCLUDE_DIR}" "${CMAKE_SOURCE_DIR}/include")

        # Copy lib files to the correct location
        message(STATUS "Copying SDL2 libraries to ${CMAKE_SOURCE_DIR}/lib")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${SDL2_LIB_DIR}" "${CMAKE_SOURCE_DIR}/lib")

        # Copy SDL2.dll to the project root
        message(STATUS "Copying SDL2.dll to the project root directory")
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BIN_DIR}/SDL2.dll" "${CMAKE_SOURCE_DIR}/SDL2.dll")

        # Clean up the versioned folder and the downloaded zip file
        execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${SDL2_EXTRACTED_FOLDER})
        execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${SDL2_DOWNLOAD_FILE})

        message(STATUS "SDL2 successfully downloaded, extracted, and moved.")
    endfunction()

    # Include directories for Windows
    set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/SDL2")
    set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

    # Check if SDL2 files are present before attempting to download
    if (NOT EXISTS "${SDL2_INCLUDE_DIR}/SDL.h" OR NOT EXISTS "${SDL2_LIB_DIR}/libSDL2.a" OR NOT EXISTS "${CMAKE_SOURCE_DIR}/SDL2.dll")
        message(STATUS "SDL2 files missing, starting download...")
        download_sdl2()
    else()
        message(STATUS "SDL2 files already exist, skipping download.")
    endif()

    # Include SDL2 directories
    include_directories("${SDL2_INCLUDE_DIR}")
    link_directories("${SDL2_LIB_DIR}")

else()
    # Linux-specific logic

    # Check for SDL2
    find_package(SDL2 REQUIRED)

    # Include SDL2 directories
    if (SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS})
        link_directories(${SDL2_LIBRARIES})
    else()
        message(FATAL_ERROR "SDL2 not found. Please install SDL2 using your package manager.")
    endif()
endif()

# Include the src directory for other headers
include_directories("${CMAKE_SOURCE_DIR}/include")

# Gather all the source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Define the executable and link to the source files
add_executable(QR_Code_Gen ${SOURCES})

set_target_properties(QR_Code_Gen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Link SDL2 libraries to the executable
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(QR_Code_Gen SDL2main SDL2)
else()
    target_link_libraries(QR_Code_Gen SDL2::SDL2 SDL2::SDL2main)
endif()

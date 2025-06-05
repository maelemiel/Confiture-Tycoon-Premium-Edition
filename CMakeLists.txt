cmake_minimum_required(VERSION 3.10)
project(UltraDualDeathRun2DeluxeEditionRemastered)
set(CMAKE_CXX_STANDARD 20)

# Raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5e6cdf3
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Raylib C++
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG be2efd4
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# C++ Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Collect all source files
file(GLOB_RECURSE SOURCES
"src/*.cpp"
"src/*.hpp"
"src/*.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link raylib
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)

# Copy assets folder to build directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
         DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()

# Platform-specific configurations
if(WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
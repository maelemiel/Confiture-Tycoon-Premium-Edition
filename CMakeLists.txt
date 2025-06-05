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

# Source files
set(SOURCE_FILES
        src/main.cpp)

# Executable setup
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)

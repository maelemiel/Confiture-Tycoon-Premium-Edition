cmake_minimum_required(VERSION 3.10)
project(UltraDualDeathRun2DeluxeEditionRemastered)
set(CMAKE_CXX_STANDARD 20)

# Raylib
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)

# Raylib C++
FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v5.5.0
)
FetchContent_MakeAvailable(raylib_cpp)

# C++ Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Collect all source files
set(SOURCES
        src/Events/EventManager.cpp
        src/Events/EventManager.hpp
        src/Events/IEvent.cpp
        src/Events/IEvent.hpp
        src/Events/MeteorEvent.cpp
        src/Events/MeteorEvent.hpp
        src/Particle/ParticleSystem.cpp
        src/Particle/ParticleSystem.hpp
        src/Particle/Particle.cpp
        src/Particle/Particle.hpp
        src/Structures/Abstracts/IStructure.hpp
        src/Structures/Abstracts/AHabitation.hpp
        src/Structures/Abstracts/AHabitation.cpp
        src/Structures/Abstracts/AOxygenProducer.hpp
        src/Structures/Abstracts/AOxygenProducer.cpp
        src/Structures/Abstracts/AResourceProducer.hpp
        src/Structures/Abstracts/AResourceProducer.cpp
        src/Structures/Factory/Factory.cpp
        src/Structures/Factory/Factory.hpp
        src/Structures/Tree.hpp
        src/Structures/Generator.hpp
        src/Structures/House.hpp
        src/UI/UI.cpp
        src/UI/UI.hpp
        src/UI/Drawer.cpp
        src/UI/Drawer.hpp
        src/Game.cpp
        src/Game.hpp
        src/main.cpp
        src/Map.cpp
        src/Map.hpp
        src/ResourceManager.cpp
        src/ResourceManager.hpp
        src/Tile.cpp
        src/Tile.hpp
        src/Window.cpp
        src/Window.hpp
        src/Camera.cpp
        src/Camera.hpp
        src/Scenes/AScene.cpp
        src/Scenes/AScene.hpp
        src/Scenes/Impl/DeathScreen.cpp
        src/Scenes/Impl/DeathScreen.hpp
        src/Scenes/Impl/Main.cpp
        src/Scenes/Impl/Main.hpp
        src/Scenes/Impl/Splashscreen.cpp
        src/Scenes/Impl/Splashscreen.hpp
        src/UI/DualityBar.cpp
        src/UI/DualityBar.hpp
        src/UI/DrawerButton.cpp
        src/UI/DrawerButton.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include headers directories
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

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

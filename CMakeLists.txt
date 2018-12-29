cmake_minimum_required(VERSION 3.9)
project(RedArrow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

find_package(SFML REQUIRED COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})

add_executable(RedArrow Source/main.cpp Source/Engine/GameState.cpp Source/Engine/GameState.h Source/Engine/StateManager.cpp Source/Engine/StateManager.h Source/Engine/GameEngine.cpp Source/Engine/GameEngine.h Source/Application.cpp Source/Application.h)

target_link_libraries(RedArrow ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
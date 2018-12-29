cmake_minimum_required(VERSION 3.9)
project(RedArrow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

find_package(SFML REQUIRED COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})

add_executable(RedArrow Source/main.cpp)

target_link_libraries(RedArrow ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
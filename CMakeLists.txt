cmake_minimum_required(VERSION 3.2)
project(RedArrow)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

#for icon
set(RES_FILES "")
if(MINGW)
 set(RES_FILES "ressources.rc")
 set(CMAKE_RC_COMPILER_INIT windres)
 ENABLE_LANGUAGE(RC)
 SET(CMAKE_RC_COMPILE_OBJECT
 "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

add_executable(RedArrow ${RES_FILES} ${SOURCE_FILES} Ship.cpp Ship.h PlayerShip.cpp PlayerShip.h EnnemyShip.cpp EnnemyShip.h Projectile.cpp Projectile.h RedArrowSinglePlayer.cpp RedArrowSinglePlayer.h RedArrowMultiPlayer.cpp RedArrowMultiPlayer.h RedArrowMenu.cpp RedArrowMenu.h Loot.cpp Loot.h ConfigFileManager.cpp ConfigFileManager.h)

#link sfml
set(SFML_ROOT "E:/SFML-2.3/")
set(CMAKE_MODULE_PATH "E:/SFML-2.3/Cmake/Modules/")
find_package(SFML 2.3 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(RedArrow ${SFML_LIBRARIES})
endif()

#link json libraries

cmake_minimum_required(VERSION 3.19)
project(SuperMarioBrosClone VERSION 1.0)
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)

set(PROJECT_HEADERS
	include/Game.h
	include/Player.h
	include/World/World.h
	include/UI/UIManager.h
	include/Enemies/Enemy.h
	include/Enemies/Goomba.h
	include/Enemies/Spikie.h
	include/Enemies/PiranhaPlant.h
	include/Coins/Coins.h
)

set(PROJECT_SOURCES 
	main.cpp
	source/Game.cpp
	source/Player.cpp
	source/World/World.cpp
	source/UI/UIManager.cpp
	source/Enemies/Enemy.cpp
	source/Enemies/Goomba.cpp
	source/Enemies/Spikie.cpp
	source/Enemies/PiranhaPlant.cpp
	source/Coins/Coins.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include )

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
 SuperMarioBrosClone
 main.cpp
 ${PROJECT_FILES}
)

target_link_libraries(
 SuperMarioBrosClone
 sfml-graphics
)


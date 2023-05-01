# CMakeList.txt : CMake project for MonopolyCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Monopoly")

# Copy data directory to build directory
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Add source to this project's executable.
add_executable (Monopoly "main.cpp" "./objects/player.cpp" "./objects/gameobject.cpp" "./game/game.cpp" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Monopoly PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

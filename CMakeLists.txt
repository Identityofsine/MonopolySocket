﻿# CMakeList.txt : CMake project for MonopolyCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Monopoly")




# set the path to the Lua source directory
set(LUA_SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/lua_src)

# add the Lua source files as a library
add_library(lua STATIC
        "${LUA_SOURCE_DIR}/lapi.c"
        "${LUA_SOURCE_DIR}/lapi.h"
        "${LUA_SOURCE_DIR}/lauxlib.c"
        "${LUA_SOURCE_DIR}/lauxlib.h"
        "${LUA_SOURCE_DIR}/lbaselib.c"
        #"${LUA_SOURCE_DIR}/lbitlib.c"
        "${LUA_SOURCE_DIR}/lcode.c"
        "${LUA_SOURCE_DIR}/lcode.h"
        "${LUA_SOURCE_DIR}/lcorolib.c"
        "${LUA_SOURCE_DIR}/lctype.c"
        "${LUA_SOURCE_DIR}/lctype.h"
        "${LUA_SOURCE_DIR}/ldblib.c"
        "${LUA_SOURCE_DIR}/ldebug.c"
        "${LUA_SOURCE_DIR}/ldebug.h"
        "${LUA_SOURCE_DIR}/ldo.c"
        "${LUA_SOURCE_DIR}/ldo.h"
        "${LUA_SOURCE_DIR}/ldump.c"
        "${LUA_SOURCE_DIR}/lfunc.c"
        "${LUA_SOURCE_DIR}/lfunc.h"
        "${LUA_SOURCE_DIR}/lgc.c"
        "${LUA_SOURCE_DIR}/lgc.h"
        "${LUA_SOURCE_DIR}/linit.c"
        "${LUA_SOURCE_DIR}/liolib.c"
        "${LUA_SOURCE_DIR}/llex.c"
        "${LUA_SOURCE_DIR}/llex.h"
        "${LUA_SOURCE_DIR}/llimits.h"
        "${LUA_SOURCE_DIR}/lmathlib.c"
        "${LUA_SOURCE_DIR}/lmem.c"
        "${LUA_SOURCE_DIR}/lmem.h"
        "${LUA_SOURCE_DIR}/loadlib.c"
        "${LUA_SOURCE_DIR}/lobject.c"
        "${LUA_SOURCE_DIR}/lobject.h"
        "${LUA_SOURCE_DIR}/lopcodes.c"
        "${LUA_SOURCE_DIR}/lopcodes.h"
        "${LUA_SOURCE_DIR}/loslib.c"
        "${LUA_SOURCE_DIR}/lparser.c"
        "${LUA_SOURCE_DIR}/lparser.h"
        "${LUA_SOURCE_DIR}/lprefix.h"
        "${LUA_SOURCE_DIR}/lstate.c"
        "${LUA_SOURCE_DIR}/lstate.h"
        "${LUA_SOURCE_DIR}/lstring.c"
        "${LUA_SOURCE_DIR}/lstring.h"
        "${LUA_SOURCE_DIR}/lstrlib.c"
        "${LUA_SOURCE_DIR}/ltable.c"
        "${LUA_SOURCE_DIR}/ltable.h"
        "${LUA_SOURCE_DIR}/ltablib.c"
        "${LUA_SOURCE_DIR}/ltm.c"
        "${LUA_SOURCE_DIR}/ltm.h"
        #"${LUA_SOURCE_DIR}/lua.c"
        #"${LUA_SOURCE_DIR}/lua.h"
        "${LUA_SOURCE_DIR}/lua.hpp"
        #"${LUA_SOURCE_DIR}/luac.c"
        "${LUA_SOURCE_DIR}/luaconf.h"
        "${LUA_SOURCE_DIR}/lualib.h"
        "${LUA_SOURCE_DIR}/lundump.c"
        "${LUA_SOURCE_DIR}/lundump.h"
        "${LUA_SOURCE_DIR}/lutf8lib.c"
        "${LUA_SOURCE_DIR}/lvm.c"
        "${LUA_SOURCE_DIR}/lvm.h"
        "${LUA_SOURCE_DIR}/lzio.c"
        "${LUA_SOURCE_DIR}/lzio.h"
)

# Add source to this project's executable.
add_executable (Monopoly "main.cpp" "./objects/player.cpp" "./objects/gameobject.cpp" "./game/game.cpp" "main.h" "lua_functions/lua_func.cpp" "server/server.cpp")



add_custom_command(TARGET Monopoly POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lua
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/lua ${CMAKE_BINARY_DIR}/lua
)


target_link_libraries( Monopoly PUBLIC lua )

set(LUA_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/lua_src)
target_include_directories(Monopoly PRIVATE ${LUA_INCLUDE_DIRS})

set(LUA_BRIDGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/includes/LuaBridge)
target_include_directories(Monopoly PRIVATE ${LUA_BRIDGE_INCLUDE_DIR})




if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Monopoly PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

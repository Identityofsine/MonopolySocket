#pragma once
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "../objects/gameobjects.h"
#include "engine_passthrough.h"
#include <vector>
#include <iostream>
#include <random>
#include <functional>

int testAdd(int x, int y) {
	return x + y;
}

void simplePrint(std::string string) {
	std::cout << string << std::endl;
}

using namespace Monopoly;
void importPlayerStructureIntoLua(lua_State* L) {
	luabridge::getGlobalNamespace(L)
    .beginClass<Player>("Player")
      .addConstructor<void (*)()>()
      .addConstructor<void (*)(std::string, Money)>()
      .addFunction("addMoney", &Player::addMoney)
      .addFunction("canBuildStructure", &Player::canBuildStructure)
      .addFunction("buyProperty", &Player::buyProperty)
      .addFunction("addProperty", &Player::addProperty)
      .addFunction("takeMoney", &Player::takeMoney)
      .addFunction("setMoney", &Player::setMoney)
      .addFunction("setInJail", &Player::setInJail)
      .addFunction("inJail", &Player::inJail)
      .addFunction("setPosition", &Player::setPosition)
      .addFunction("getPosition", &Player::getPosition)
      .addFunction("notifyTurn", &Player::notifyTurn)
      .addFunction("notifyDecision", &Player::notifyDecision)
      .addFunction("getName", &Player::getName)
    .endClass();
}

void importLandableStructureIntoLua(lua_State* L) {

}

int lua_randomnumber(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(l, r);
    return distrib(gen);
}

/**
	@brief This Function is called on program execution, it loads a lua state variable and loads in all the associated methods. The plan is to have a function in lua ("pull_chance_card"), that returns a table of : "Card Content", "Card Index". It will take a player object and modify the player's position, money, or properties depending on the card.
*/
lua_State* loadLuaChanceCard() {
	lua_State* l_chance = luaL_newstate();
	luaL_openlibs(l_chance);
	luabridge::getGlobalNamespace(l_chance)
	.addFunction("print", &simplePrint)
	.addFunction("random", &lua_randomnumber);
	luaL_dofile(l_chance, "lua/chance.lua");
	return l_chance;
}

/**
* @brief Do not use unless lua_state is initialized
*/
void importLuaFunction(lua_State* L) {
  luabridge::getGlobalNamespace(L)
	.addFunction("print", &simplePrint)
	.addFunction("random", &lua_randomnumber);
}

using namespace luabridge;
template<typename ...args>
void addEngineFunctionToLua(lua_State* L, Player* player, std::vector<EngineMethod<args...>>* methods) {
    if (methods->empty()) return;

    for (EngineMethod<args...>* d = methods->data(); d < methods->data() + methods->size(); ++d) {
        std::function wrappedMethod = [player,d](int value) {
            d->method(player, value);
        };
        luabridge::getGlobalNamespace(L)
            .addFunction(d->name.c_str(), wrappedMethod);
    }
}

template<typename ...args>
void pullChanceCard(lua_State* L, Player* player, std::vector<EngineMethod<args...>>* methods) {
	lua_State* chance_script = loadLuaChanceCard();
	importPlayerStructureIntoLua(chance_script);
    addEngineFunctionToLua<args...>(chance_script, player, methods);
	LuaRef grabChanceCard = getGlobal(chance_script, "PullChanceCard");
    try {
	    grabChanceCard(&player);
    }
    catch (LuaException e) {
        printf("\n[LUA ERROR]: %s\n", e.what());
    }
	//lua_close(chance_script);
}

/**
	@brief This Function is called on program execution, it loads a lua state variable and loads in all the associated methods. The plan is to have a function in lua ("pull_chance_card"), that returns a table of : "Card Content", "Card Index". It will take a player object and modify the player's position, money, or properties depending on the card.
*/
void loadLuaCommunityCard(std::string path) {

}
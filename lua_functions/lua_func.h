#pragma once
#include <lua.hpp>
#include "../includes/jeremyong/selene.h"
#include "../objects/gameobjects.h"
#include <iostream>

int testAdd(int x, int y) {
	return x + y;
}

void simplePrint(std::string string) {
	std::cout << string << std::endl;
}

void startLua(sel::State* stateVariable, std::string path) {
	sel::State state = &stateVariable; //lua file
	state["print"] = &simplePrint;
	state["testAdd"] = &testAdd;
	state.Load(path);

}

int lua_randomnumber(int l, int r) {

}

/**
	@brief This Function is called on program execution, it loads a lua state variable and loads in all the associated methods. The plan is to have a function in lua ("pull_chance_card"), that returns a table of : "Card Content", "Card Index". It will take a player object and modify the player's position, money, or properties depending on the card.
*/
void loadLuaChanceCard(sel::State* stateVariable, std::string path) {

}

using namespace Monopoly;
void pullChanceCard(Player* player) {
	sel::State stateVariable;
	stateVariable["print"] = &simplePrint;
	//stateVariable["current_player"].SetObj(player,
	//	"getPosition", &Player::getPosition,
	//	"setPosition", &Player::setPosition,
	//	"");
	stateVariable.Load("lua/chance.lua");
	std::string sex = stateVariable["PullChanceCard"](player);
}

/**
	@brief This Function is called on program execution, it loads a lua state variable and loads in all the associated methods. The plan is to have a function in lua ("pull_chance_card"), that returns a table of : "Card Content", "Card Index". It will take a player object and modify the player's position, money, or properties depending on the card.
*/
void loadLuaCommunityCard(sel::State* stateVariable, std::string path) {

}
#pragma once
#include <lua.hpp>
#include "../includes/jeremyong/selene.h"
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
#include <lua.hpp>
#include <stdio.h>
#include "objects/gameobjects.h"
#include "game/game.h"
#include "main.h"
#include "includes/jeremyong/selene.h"
#include "lua_functions/lua_func.h"
using namespace Monopoly;


int main()
{

    sel::State state;
    startLua(&state, "lua/test.lua");

    //MonopolyGame game = MonopolyGame(4235123);
    //Player kevin = Player("Kevin", 0);
    //Player gabe = Player("Gabe", 0);
    //game.addPlayer(&kevin);
    //game.addPlayer(&gabe);

    //game.startGame(MonopolyRules(999999));


    return 0;
}
#include <lua.hpp>
#include <stdio.h>
#include "objects/gameobjects.h"
#include "game/game.h"
#include "main.h"
#include "server/server.hpp"
#include "includes/jeremyong/selene.h"
using namespace Monopoly;


int main()
{
    
    
    MonopolyServer::server();
    // MonopolyGame game = MonopolyGame(4235123);
    // Player kevin = Player("Kevin", 0);
    // Player gabe = Player("Gabe", 0);
    // game.addPlayer(&kevin);
    // game.addPlayer(&gabe);

    // game.startGame(MonopolyRules(999999));


    return 0;
}
#include <stdio.h>
#include "objects/gameobjects.h"
#include "game/game.h"
#include "main.h"
#include <thread>
using namespace Monopoly;

int main()
{
    MonopolyGame game = MonopolyGame(4235123);
    Player kevin = Player("Kevin", 0);
    Player gabe = Player("Gabe", 0);
    game.addPlayer(&kevin);
    game.addPlayer(&gabe);

    game.startGame(MonopolyRules(999999));


    return 0;
}
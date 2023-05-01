#include <stdio.h>
#include "objects/gameobjects.h"
#include "game/game.h"
#include "main.h"
using namespace Monopoly;

int main()
{
    MonopolyGame game = MonopolyGame(4235123);
    Player player = Player(800);
    Landable Wyndanch = Landable("Wyndanch Ave", 180, true, true, PropertyColor(0, 2));
    Landable Brentwood = Landable("Brentwood Ave", 40, true, true, PropertyColor(0, 2));
    player.buyProperty(&Wyndanch);
    player.buyProperty(&Brentwood);

    
    
    Wyndanch.purchaseStructure(&player);

    return 0;
}
#pragma once
#include "vector"
#include "../objects/gameobjects.h"


namespace Monopoly{


    struct MonopolyRules {
    public:
        Money staringCash;

    };

    struct MonopolyGame{
    private:
        unsigned int gameID;
        Player* playerInTurn; // this is the player's turn, only listen to him.
        std::vector<Player*> players = std::vector<Player*>();
        Landable* spaces;
    public:
        MonopolyGame(unsigned int gameID);
        bool addPlayer(Player* player);
        bool startGame();
        bool movePlayer(Player* player, int spaces);
 
    };
}
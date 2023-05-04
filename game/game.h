#pragma once
#include "vector"
#include "../objects/gameobjects.h"


namespace Monopoly{

    int generateRandomDiceNumber();

    int combinePair(std::pair<int, int> pair);

    struct MonopolyRules {
    public:
        MonopolyRules(Money cash);
        Money startingCash;

    };

    struct MonopolyGame{
    private:
        unsigned int gameID;
        int playerIndex = 0;
        Player* playerInTurn; // this is the player's turn, only listen to him.
        std::vector<Player*> players = std::vector<Player*>();
        std::vector<Player*> notPlaying = std::vector<Player*>(); //this is for players who are either spectating or bankrupt
        Landable* spaces;
        bool hasStarted = false;
    public:
        MonopolyGame(unsigned int gameID);
        bool addPlayer(Player* player);
        bool startGame(MonopolyRules monopolyRules);
        bool movePlayer(Player* player, int spaces, bool fromLUA = false);
        std::pair<int, int> rollDice(Player* player);
        void runEngine();
        void handleMonopolyDecision(MonopolyDecision event, Player* player, Landable* spot);
        bool buyProperty(Player* player, Landable* spot);
    };


}
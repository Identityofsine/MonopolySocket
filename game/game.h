#pragma once
#include "vector"
#include "../objects/gameobjects.h"


namespace Monopoly{
    struct MonopolyGame{
    private:
        unsigned int gameID;
        std::vector<Player*> players = std::vector<Player*>();
        Landable* spaces;
    public:
        MonopolyGame(unsigned int gameID);
    };
}
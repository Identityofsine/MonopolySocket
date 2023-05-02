#include "game.h"
#include "../includes/nlohmann/json.hpp"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <ios> // Include the <ios> header file

using namespace Monopoly;
using json = nlohmann::json;
namespace Monopoly
{
    
    MonopolyRules::MonopolyRules(Money money) {
        this->startingCash = money;
    }


    void importSpacesJson(Landable* array, size_t size);
    void displaySpaces(Landable* array, size_t size);
    /**
     * @brief Construct a new Monopoly Game:: Monopoly Game object
     * 
     */
    MonopolyGame::MonopolyGame(unsigned int gameID){
        this->gameID = gameID;
        this->spaces = new Landable[40];
        importSpacesJson(this->spaces, 40);
        displaySpaces(this->spaces, 40);
        //load json into memory

    }

    void importSpacesJson(Landable array[], size_t size) {
        std::ifstream f("data/spaces.json");

        json data = json::parse(f)["spaces"];
        int i = 0;
        for(auto it : data){
            if(i > 40) break;
            std::string name = it["name"].get<std::string>();
            array[i++] = Landable(name, 500, false, false, PropertyColor(0, 10)); 
        }
    }

    void displaySpaces(Landable array[], size_t size) {
        for(size_t i = 0; i < size; i++) {
            printf("Landable : %s\n", array[i].name.c_str());
        }
    } 

    bool MonopolyGame::startGame(MonopolyRules rules) {
        if (this->hasStarted) return false;
        if (this->players.empty()) return false;
        this->hasStarted = true;
        for (auto player : this->players) {
            player->setMoney(rules.startingCash);
            player->setInJail(false);
        }
        playerInTurn = this->players.at(0);
    }

    bool MonopolyGame::addPlayer(Player* player) {
        if (this->hasStarted) return false;
        this->players.push_back(player);
        return true;
    }

    bool MonopolyGame::movePlayer(Player* player, int spaces) {
        if (!hasStarted) return false;
        if(player->getID() == this->playerInTurn->getID()) {
            if(int newPOS = player->getPosition() + spaces < 40)
                player->setPosition(newPOS);
            else {
                player->setPosition(newPOS - 40);
            }
            int playerPOS = player->getPosition();
            this->spaces[playerPOS].onLand();
            printf("%s is now at %s", player->getName().c_str(), this->spaces[playerPOS].name.c_str());
            return true;
        }
        else
            return false;
    }

    std::pair<int, int> MonopolyGame::rollDice(Player* player) {
        if (player->getID() == this->playerInTurn->getID()) {
            int d1, d2;
            d1 = generateRandomDiceNumber();
            d2 = generateRandomDiceNumber();
            if (d1 == d2) {
                //doubles
                ;
            }
            else {
                if(playerIndex >= this->players.size())
                    playerIndex = 0; // go back to first person
                else
                playerIndex = 1;
            }
            this->playerInTurn = players.at(playerIndex);
            return std::make_pair(d1, d2);
        }
        return std::make_pair(-1, -1); // can't believe they tried to roll on their turn.
    }

    /**
    * Generate a random Dice Roll
    * 
    * @returns std::pair, a pair of numbers.
    */
    int generateRandomDiceNumber() {
        srand(time(nullptr));
        int randomNumber = rand() % 6 + 1;
        return randomNumber;
    }


    /**
        Combines a Pair

        @returns a single Interger from the combination of two pairs.
    */
    int combinePair(std::pair<int,int> pair) {
        return pair.first + pair.second;
    }

}

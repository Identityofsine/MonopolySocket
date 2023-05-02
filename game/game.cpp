#include "game.h"

#include "../includes/nlohmann/json.hpp"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <ios>
#include <thread>
#include <chrono>         // std::chrono::seconds

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

    void loadLUA() {

    }

    void importSpacesJson(Landable array[], size_t size) {
        std::ifstream f("data/spaces.json");

        json data = json::parse(f)["spaces"];
        int i = 0;
        auto lambda = [](Player* player, MonopolyEvent event){
            player->notifyDecision(event);
        };
        for(auto it : data){
            if(i > 40) break;
            std::string name = it["name"].get<std::string>();
            array[i++] = Landable(name, 500, true, true, PropertyColor(0, 10), lambda); 
        }
    }

    void displaySpaces(Landable array[], size_t size) {
        for(size_t i = 0; i < size; i++) {
            printf("Landable : %s\n", array[i].name.c_str());
        }
    } 
    
    void MonopolyGame::runEngine() {
        while (this->hasStarted) {
            ; //tick
            Player* player = playerInTurn;
            player->notifyTurn();
            int result = combinePair(rollDice(player));
            printf("You Rolled a : %d\n", result);
            movePlayer(player, result);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
        runEngine();
    }



    bool MonopolyGame::addPlayer(Player* player) {
        if (this->hasStarted) return false;
        this->players.push_back(player);
        return true;
    }

    bool MonopolyGame::buyProperty(Player* player, Landable* property){
        if(property->isOwned() || !property->isBuyable()) return false;
        bool result = player->takeMoney(property->getPrice());
        if(result){
            property->setOwned(player);
            printf("%s now owns : %s\n", player->getName().c_str(), property->name.c_str());
            return true;
        } else 
            return false;
    }

    void MonopolyGame::handleMonopolyDecision(MonopolyDecision event, Player* player, Landable* spot){
        if(event == BUY){
            bool result = this->buyProperty(player, spot);
            if(!result)
                printf("You cannot buy this property...\n");
        }

    }

    bool MonopolyGame::movePlayer(Player* player, int spaces) {
        if (!hasStarted) return false;
        if ((player->getPosition() + spaces + 1) < 40)
            player->setPosition(player->getPosition() + spaces + 1);
        else {
            player->setPosition(player->getPosition() + spaces - 39);
        }
        int playerPOS = player->getPosition();
        MonopolyDecision _response = this->spaces[playerPOS].onLand(player);
        handleMonopolyDecision(_response, player, &(this->spaces[playerPOS]));
        // printf("%s is now at %s\n", player->getName().c_str(), this->spaces[playerPOS].name.c_str());
        return true;
    }



    std::pair<int, int> MonopolyGame::rollDice(Player* player) {
        if (player->getID() == this->playerInTurn->getID()) {
            int d1, d2;
            d1 = generateRandomDiceNumber();
            d2 = generateRandomDiceNumber();
            if (d1 == d2) {
                //doubles
                printf("%s got Doubles! \n", player->getName().c_str())
                ;
            }
            else {
                if(playerIndex + 1 >= this->players.size())
                    playerIndex = 0; // go back to first person
                else
                playerIndex++;
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
        static bool initialized = false;
        if (!initialized) {
            srand(time(nullptr));
            initialized = true;
        }
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

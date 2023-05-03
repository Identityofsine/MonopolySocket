#include "game.h"
#include "../includes/nlohmann/json.hpp"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <ios>
#include <thread>
#include <chrono>         // std::chrono::seconds
#include <functional>

using namespace Monopoly;
using json = nlohmann::json;


namespace Monopoly
{
    
    MonopolyRules::MonopolyRules(Money money) {
        this->startingCash = money;
    }



    void importSpacesJson(Landable* array, size_t size);
    void displaySpaces(Landable* array, size_t size);
    int generateRandomDiceNumber();
    /**
     * @brief Construct a new Monopoly Game:: Monopoly Game object
     * 
     */
    MonopolyGame::MonopolyGame(unsigned int gameID) {
        this->gameID = gameID;
        this->spaces = new Landable[40];
        importSpacesJson(this->spaces, 40);
        //displaySpaces(this->spaces, 40);
        //load json into memory

    }

    void importSpacesJson(Landable array[], size_t size) {
        std::ifstream f("data/spaces.json");
        std::ifstream z("data/color.json");
        json data = json::parse(f)["spaces"];
        json color_data = json::parse(z)["groups"];
        int i = 0;

        for(auto it : data){
            if(i > 40) break;
            std::string _j_name = it["name"].get<std::string>();
            bool _j_buyable = it["buyable"].get<bool>();
            int _j_groupID = 0;
            int _j_money = 0;
            try {
                _j_groupID = it["group"].get<int>();
                _j_money = it["price"].get<double>();
            }
            catch (json::exception err) {
                _j_groupID = 10;
                _j_money = -1;
                std::cout << "JSON ERROR : " << err.what() << std::endl;
            }
            PropertyColor ppc = PropertyColor(_j_groupID, color_data.at(_j_groupID)["numberOfProperties"].get<int>());
            bool _j_structureable = _j_buyable && _j_groupID != 10 && _j_groupID != 11 ? true : false;
            std::function<void(Landable* landable, Player* player, MonopolyEvent event)> lambda = [](Landable* landable, Player* player, MonopolyEvent event) {};

            switch (_j_groupID) {
                case 9:
                    lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                        if (!landable->isOwned()) return;
                        printf("\n!Rolling Again...!\n");
                        int roll = generateRandomDiceNumber();
                        int roll2 = generateRandomDiceNumber();
                        int result = roll + roll2;
                        result = result * 4;
                        player->takeMoney(result);
                        landable->getOwner()->addMoney(result);
                        printf("%s had to pay %d to %s\n", player->getName().c_str(), result, landable->getOwner()->getName().c_str());
                    };
                    break;
                case 10:
                    lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                        printf("\n!COMMUNITY CARD!\n");
                        //pull card out, then send to player.
                        //run card function using lua.
                    };
                    break;
                case 11:
                    lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                        printf("\n!CHANCE CARD!\n");
                        //pull card out, then send to player.
                        //run card function using lua.
                    };
                    break;
                case 12:
                    lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                        //tax;
                        printf("%s time time to pay : $%d!!!\n", landable->name.c_str(), landable->getPrice());
                        player->takeMoney(landable->getPrice());
                    };
                    break;
                case 16:
                    lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                        printf("%s landed on go, heres 400 dollars!\n", player->getName().c_str());

                        player->addMoney(400);
                    };
                    break;
                default:
                    break;
            }
            array[i++] = Landable(_j_name, _j_money, _j_buyable, _j_structureable, PropertyColor(0, 10), lambda);

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

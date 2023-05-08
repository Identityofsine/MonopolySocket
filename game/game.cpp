#include "game.h"
#include "../lua_functions/lua_func.h"
#include "../includes/nlohmann/json.hpp"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <ios>
#include <thread>
#include <chrono>         // std::chrono::seconds
#include <functional>

#define TICK_RATE_MS 750

#ifdef _WIN32
#include <cstdlib>
#endif


using namespace Monopoly;
using json = nlohmann::json;




namespace Monopoly
{
    /**
     * @brief Constructs a new instance of MonopolyRules, a simple struct to hold all of the data for initialization.
     * 
     * @param money 
     */
    MonopolyRules::MonopolyRules(Money money) {
        this->startingCash = money;
    }



    void importSpacesJson(Landable* array, size_t size, MonopolyGame* engine);
    void LinkLuaIntoLandable(Landable* array, size_t size, MonopolyGame* engine);

    void displaySpaces(Landable* array, size_t size);
    int generateRandomDiceNumber();
    /**
     * @brief Construct a new Monopoly Game:: Monopoly Game object
     * 
     */
    MonopolyGame::MonopolyGame(unsigned int gameID) {
        this->gameID = gameID;
        this->spaces = new Landable[40];
        MonopolyGame* engine_ptr = this; // Declare a pointer to the instance
        importSpacesJson(this->spaces, 40, engine_ptr);
        //displaySpaces(this->spaces, 40);
        //load json into memory

    }

    /**
     * This function uses an ifstream to load a json file from ~/data/spaces and ~/data/color to generate both Landable objects and their associated behaviors.
     * 
     * @brief This function is subject to change in the future. Intializes the Landable array.
     * 
     * @param array 
     * @param size 
     */
    void importSpacesJson(Landable array[], size_t size, MonopolyGame* engine) {
        std::ifstream f("data/spaces.json");
        std::ifstream z("data/color.json");
        json data = json::parse(f)["spaces"]; // all the spaces in spaces.json
        json color_data = json::parse(z)["groups"]; //all the color_data in color.json
        int i = 0; //index
        //loop through data array
        for(auto it : data){
            if(i > size) break; //break if size is hit(somehow)
            std::string _j_name = it["name"].get<std::string>();
            bool _j_buyable = it["buyable"].get<bool>();
            int _j_groupID = 0;
            int _j_money = 0;
            //try to read _j_groupID and _j_money from the json file, this can be removed in the future as a bug was happening where it would read null.
            try {
                _j_groupID = it["group"].get<int>();
                _j_money = it["price"].get<double>();
            }
            catch (json::exception err) {
                _j_groupID = 10;
                _j_money = -1;
                std::cout << "JSON ERROR : " << err.what() << std::endl;
            }
            //ppc object are for holding PropertyInformation, such as Boardwalk being a dark blue property and it only having one sibiling (total 2).
            PropertyColor ppc = PropertyColor(_j_groupID, color_data.at(_j_groupID)["numberOfProperties"].get<int>());
            bool _j_structureable = _j_buyable && _j_groupID != 10 && _j_groupID != 11 ? true : false;
            //Labmda function used for unique behavior, such as landing on GO or going to jail, etc.
            //using auto lambda = [](args){}; was a possibility but it wasn't possible to change lambda after inital assignment.  
 
            array[i++] = Landable(_j_name, _j_money, _j_buyable, _j_structureable, ppc); 
        }
    }

    void LinkLuaIntoLandable(Landable arr[], size_t size, MonopolyGame engine) {
        for (int i = 0; i < size; i++) {
            auto spot = arr[i];
            std::function<void(Landable* landable, Player* player, MonopolyEvent event)> lambda = [engine](Landable* landable, Player* player, MonopolyEvent event) {};

            //switch ID (mapped to color.json)
            switch (spot.getColorID().getColorID()) {
            case 9: //Utility
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
            case 10: //Community Chest
                lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                    printf("\n!COMMUNITY CARD!\n");
                    //pull card out, then send to player.
                    //run card function using lua.
                };
                break;
            case 11: //Chance
                lambda = [&engine](Landable* landable, Player* player, MonopolyEvent event) {
                    printf("\n!CHANCE CARD!\n");
                    //pull card out, then send to player.
                    //run card function using lua.
                    std::vector<EngineMethod<Player*, int>> chanceMethods = std::vector<EngineMethod<Player*, int>>();

                    std::function<void(Player* player, int spaces)> engine_move = [&engine](Player* player, int spaces) {
                        std::cout << "\nENGINE_MOVE_RAN" << std::endl;
                        engine.movePlayer(player, spaces, true);
                    };

                    chanceMethods.emplace_back("engine_moveplayer", engine_move);
                    lua_State* state = loadLuaChanceCard();
                    pullChanceCard<Player*, int>(state, player, &chanceMethods);
                };
                break;
            case 12: //any type of tax (uses the Landable's properties to deal money and debt). In the future, the money will go to the pot.
                lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                    //tax;
                    printf("%s time time to pay : $%d!!!\n", landable->name.c_str(), landable->getPrice());
                    player->takeMoney(landable->getPrice());
                };
                break;
            case 16: //GO
                lambda = [](Landable* landable, Player* player, MonopolyEvent event) {
                    printf("%s landed on go, heres 400 dollars!\n", player->getName().c_str());

                    player->addMoney(400);
                };
                break;
            default:
                lambda = [&engine](Landable* landable, Player* player, MonopolyEvent event) {

                };
                break;
            }
            arr[i].setLandBehavior(lambda);
        }
    }


    /**
     * 
     * Simple Debug Function that displays all the spaces stored in a Landable array.
     * 
     * @brief Debug Function, Displays all the spaces
     * 
     * @param array 
     * @param size 
     */
    void displaySpaces(Landable array[], size_t size) {
        for(size_t i = 0; i < size; i++) {
            printf("Landable : %s\n", array[i].name.c_str());
        }
    } 
    
    /**
     * 
     * This function is very important for behaviour and the entire game. This starts the MonopolyGame Engine for this specific game. It executes logic every two seconds and multiple revisions will be made for this function. The problem right now is waiting for user input without wasting resources; std::cin is fine but when we use sockets it's very important to make sure no code is executed until a response from the player in turn is received.
     * 
     * @brief Initalize the Monopoly Engine and run the game at 2 ticks a second. This speed should go down as the game and program becomes more intense, especially when using a socket. 
     * 
     * 
     * 
     */
    void MonopolyGame::runEngine() {
        LinkLuaIntoLandable(this->spaces, 40, *this);
        while (this->hasStarted) {
            ; //tick
            Player* player = playerInTurn;
            #ifdef _WIN32
            //system("cls");
            #else
            system("clear");
            #endif
     
            player->notifyTurn();
            int result = combinePair(rollDice(player));
            printf("You Rolled a : %d\n", result);
            MonopolyDecision _response = movePlayer(player, result);
            handleMonopolyDecision(_response, player, &(this->spaces[player->getPosition()]));

            std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MS));
        }

    }

    /**
     * @brief Offically Starts the Game, will not start if no players are in the lobby.
     * 
     * @param rules MonopolyRules Object
     * @return true 
     * @return false 
     */
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


    /**
     * @brief Adds a player to the game; returns false if the game has started.
     * 
     * @param player 
     * @return true 
     * @return false 
     */
    bool MonopolyGame::addPlayer(Player* player) {
        if (this->hasStarted) return false;
        this->players.push_back(player);
        return true;
    }

    /**
     * @brief This function returns true if the player can buy the property and false when they cant (Not enough money, or Landable doesn't support ownership).
     * 
     * @param player 
     * @param property 
     * @return true 
     * @return false 
     */
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

    /**
     * @brief Handles a player's decision, currently only supports buying property, but eventually the player will be able to buy houses and homes on their own property, this function is subject to be removed in the future for better implementation with buying houses independent.
     * 
     * @param event MonopolyDecision Enumeration
     * @param player Player Pointer
     * @param spot Landable Pointer
     */
    void MonopolyGame::handleMonopolyDecision(MonopolyDecision event, Player* player, Landable* spot){
        if(event == BUY){
            bool result = this->buyProperty(player, spot);
            if(!result)
                printf("You cannot buy this property...\n");
        }

    }

    /**
     * @brief This function is responsible for moving the player across the board, this function also calles handleMonopolyDecision to see what the player wants to do, it's also very important to know that when the player moves, this returns false if the game isn't active or if the player is in jail.
     * 
     * @param player 
     * @param spaces 
     * @return true 
     * @return false 
     */
    MonopolyDecision MonopolyGame::movePlayer(Player* player, int spaces, bool fromLUA) {
        if (!hasStarted) return IGNORE;
        if (player->inJail()) return IGNORE;
        if ((player->getPosition() + spaces) < 40)
            player->setPosition(player->getPosition() + spaces);
        else {
            player->setPosition(player->getPosition() + spaces - 39);
        }
        int playerPOS = player->getPosition();
        MonopolyDecision _response = this->spaces[playerPOS].onLand(player);
        // if(!fromLUA)
        return _response;
    }


    bool MonopolyGame::taxPlayer(Player* player, Money amount) {
        const bool takenMoney = player->takeMoney(amount);
        if (!takenMoney) return false; //handle logic for morgating
        this->pot += amount;
    }

    void MonopolyGame::givePlayerPot(Player* player) {
        if (player->inJail()) return;
        player->addMoney(this->pot);
        this->pot = 0;
    }

    /**
     * @brief Roll dice is the heart of movement for the game. This function rolls two numbers and checks if they are doubles. This function is also responsible for changing the turn of the player. It returns the dice roll the player gets in a pair object
     * 
     * @param player Current Player.
     * @return std::pair<int, int> 
     */
    std::pair<int, int> MonopolyGame::rollDice(Player* player) {
        if (player->getID() == this->playerInTurn->getID()) {
            int d1, d2;
            d1 = generateRandomDiceNumber();
            d2 = generateRandomDiceNumber();
            if (d1 == d2) {
                //doubles
                printf("%s got Doubles! \n", player->getName().c_str());
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

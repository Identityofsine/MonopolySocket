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

}

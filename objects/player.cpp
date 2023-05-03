#include <math.h>
#include <stdio.h>
#include "gameobjects.h"
#include <iostream>
namespace Monopoly {

	/**
	 * @brief Construct a new Player:: Player object, with custom starting money
	 * 
	 * @param startingMoney 
	 */
	Player::Player(std::string name, Money startingMoney) : MonopolyObject() {
		this->name = name;
		this->money = startingMoney;
	}
	/**
	 * @brief Construct a new Player:: Player object
	 * 
	 */
	Player::Player() : Player("", 800) {

	}

	/**
	 * @brief Adds money into the player's money variable
	 * 
	 * @param new_cash 
	 * @return Money 
	 */
	Money Player::addMoney(Money new_cash) {
		this->money += new_cash;
		return money;
	}

	/** 
	 * @brief Takes money from the player's money variable, if the value will be negative money isn't taken and the method returns false.
	 * @returns boolean, was the money taken.
	*/
	bool Player::takeMoney(Money debt) {
		if (debt > this->money)
			return false; // bankrupt player if onLand();
		this->money -= debt;
		return this->money;
	}
	
	/**
	 * @brief Tries to purchase a structure, returns true if successful, false if unsuccessful (either its owned or the player doesn't have enough money)
	 * 
	 * @param property 
	 * @return true 
	 * @return false 
	 */
	bool Player::buyProperty(Landable* property) {
		bool tookMoney = this->takeMoney(property->getPrice());
		if (!tookMoney || property->isOwned()){
			this->addMoney(property->getPrice());
			return false;
		}
		else {
			property->setOwned((this));
			this->addProperty(property);
			return true;
		}
	}

	/**
	 * @brief Adds a property to vector data-structure
	 * 
	 * @param property 
	 * @return true 
	 */
	bool Player::addProperty(Landable* property) {
		ownedProperties.push_back(property);
		return true;
	}

	/**
	 * @brief Manually set the money of the player.
	 * 
	 * @param cash 
	 */
	void Player::setMoney(Money cash) {
		this->money = cash;
	}

	/**
	 * @brief Can the player build a house or hotel? Checks the colorID of the property and sees if the player has all three (or two).
	 * 
	 * @param colorID 
	 * @return true 
	 * @return false 
	 */
	bool Player::canBuildStructure(PropertyColor colorID) {
		int propCount = 0;
		for (int i = 0; i < ownedProperties.size(); i++) {
			Landable* property = ownedProperties.at(i);
			if (property->getColorID().getColorID() == colorID.getColorID()) {
				propCount++;
			}
		}
		return propCount >= colorID.getMax();
	}

	/**
	 * @brief Return the player's name
	 * 
	 * @return std::string 
	 */
	std::string Player::getName() {
		return name;
	}

	/**
	 * @brief Set the player in Jail;
	 * 
	 * @param inJail 
	 */
	void Player::setInJail(bool inJail){
		this->isInJail = inJail;
	}
	/**
	 * @brief Returns if the player is in Jail.
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Player::inJail() {
		return this->isInJail;
	}
	/**
	 * @brief Sets the position of the player, mainly used on movePlayer in MonopolyGame.
	 * 
	 * @param position 
	 */
	void Player::setPosition(int position) {
		this->position = position;
	}
	/**
	 * @brief Get the player's position.
	 * 
	 * @return int 
	 */
	int Player::getPosition() {
		return this->position;
	}

	/**
	 * @brief This is a function that acts as a subscriber to the MonopolyGame, it is called every time its the player's turn.
	 * 
	 */
	void Player::notifyTurn() {
		printf("It's your turn, %s! Type anything in to continue\n", this->name.c_str());
		// this is here to wait for an input but in the future it will not be here, instead it'll be waiting for a response from the client.
		std::string input;
		std::getline(std::cin, input); // wait for input

	}

	/**
	 * @brief This acts as a function to ask the player their decision to a certian event, either landing on a normal property or falling into jail. This function is also subject to radical change for sockets. It may even be possible that this function will be a lambda defined in the initalization of a game through sockets.
	 * 
	 * @param event 
	 * @return MonopolyDecision 
	 */
	MonopolyDecision Player::notifyDecision(MonopolyEvent event) {
		std::string input;
		printf("\nMoney : %d, Position :%d\n", money, position);

		switch(event){
			case NORMAL_LAND: // land that is normal, either unowned or unbuyable
				printf("Decide: b - Buy, h - Buy House/Hotel, any input - ignore\n");
				std::getline(std::cin, input); // wait for input
				if(input == "b"){ // buy 
					//buy;
					return BUY;

				} else if(input == "h"){ // build house
					//buy hotel;
					return BUILD_HOUSE;
				} else 
					return IGNORE; //do nothing
			break;
			case OWNED_LAND: //owned land; paying is handled by onLand
				//pay
			break;
			case JAIL: // go to jail; may not even be handled here.
				//go to jail
				printf("You're just visiting Jail...\n");

			break;
			case SPECIAL_LAND:
				//railroad or utility
			break;
			case TAX: // Landing on TAX, this is handled by onLandBehavior for tax spots, this isn't needed.
				//do something
	
			break;
			default:
				//nothing
			break;
		}
		return IGNORE;

	}
}
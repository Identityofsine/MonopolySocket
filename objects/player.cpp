#include <math.h>
#include <stdio.h>
#include "gameobjects.h"

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

	std::string Player::getName() {
		return name;
	}


	void Player::setInJail(bool inJail){
		this->isInJail = inJail;
	}
	bool Player::inJail() {
		return this->isInJail;
	}
	void Player::setPosition(int position) {
		this->position = position;
	}
	int Player::getPosition() {
		return this->position;
	}

	void Player::notifyTurn() {
		printf("It's your turn!");
	}
}
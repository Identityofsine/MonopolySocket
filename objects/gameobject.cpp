#include "gameobjects.h"
#include "math.h"
#include "stdio.h"

namespace Monopoly {


	/**
	* Simple Constructor for Monopoly Objects, All it does is create 
	*/
	MonopolyObject::MonopolyObject() {
		this->id = rand();
	}
	long MonopolyObject::getID() {
		return this->id;
	}

	/**
	* Buyable Constructor, gives a buyable thing a name and price
	* 
	* @param Name
	* @param Cost of the buyable Object
	*/
	Buyable::Buyable(std::string name, Money price) : MonopolyObject() {
		this->name = name;
		this->price = price;
		this->sellPrice = floor(price * .77);
		this->owned = false;
		this->mortagaged = false;
	}
	/**
	 * @brief This returns the price of the Buyable object
	 * 
	 * @return Money, the amount of money the Buyable costs
	 */
	Money Buyable::getPrice() {
		return this->price;
	}
	/**
	 * @brief This returnst the sell rpice of the Buyable Object
	 * 
	 * @return Money 
	 */
	Money Buyable::getSellPrice() {
		return this->sellPrice;
	}
	/**
	 * @brief Returns a boolean: Is the structure owned?
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Buyable::isOwned() {
		return this->owned;
	}
	/**
	 * @brief Set owned to true and the owner to the player using a pointer
	 * 
	 * @param owner a Player Pointer
	 */
	void Buyable::setOwned(Player* owner) {
		this->owned = true;
		this->owner = owner;
	}
	/**
	 * @brief This sets the owned by force without a player, the owner gets set to null
	 * 
	 * @param forced_state boolean
	 */
	void Buyable::setOwned(bool forced_state){
		this->owner = nullptr;
		this->owned = forced_state;
	}

	Player* Buyable::getOwner() {
		return this->owner;
	}

	/**
	 * @brief Construct a new Property Color object
	 * 
	 * @param color_id 
	 * @param max 
	 */
	PropertyColor::PropertyColor(int color_id, int max) {
		this->color_id = color_id;
		this->max = max;
	}
	/**
	 * @brief Default Constructer : a new Property Color object
	 * 
	 */
	PropertyColor::PropertyColor() : PropertyColor(-1, -1) {

	}
	/**
	 * @brief Get Property ColorID
	 * 
	 * @return int 
	 */
	int PropertyColor::getColorID() {
		return color_id;
	}
	/**
	 * @brief Get Max Properties for that color
	 * 
	 * @return int 
	 */
	int PropertyColor::getMax() {
		return max;
	}

	Landable::Landable() : Buyable("NULL", 0) {
		this->color_parent = PropertyColor(-1, -1);
		this->onLandBehavior = nullptr;
		this->buyable = false;
		this->structuresAllowed = false;
	}

	/**
	 * @brief This constructs a Landable Object but does not initialize the onLandBehavior variable
	 * 
	 * @param name 
	 * @param price 
	 * @param isBuyable 
	 * @param canHaveStructures 
	 * @param propColor 
	 */
	Landable::Landable(std::string name, Money price, bool isBuyable, bool canHaveStructures, PropertyColor propColor) : Buyable(name, price) {
		this->buyable = isBuyable;
		this->structuresAllowed = canHaveStructures;
		this->color_parent = propColor;
		this->onLandBehavior = nullptr;
	}
	/**
	 * @brief Construct a new Landable:: Landable object, but this one requires a void pointer for onLandBehavior;
	 * 
	 * @param name 
	 * @param price 
	 * @param isBuyable 
	 * @param canHaveStructures 
	 * @param propColor 
	 * @param operation 
	 */
	Landable::Landable(std::string name, Money price, bool isBuyable, bool canHaveStructures, PropertyColor propColor, std::function<void(Landable* landable, Player* player, MonopolyEvent event)> operation) : Buyable(name, price) {
		this->color_parent = propColor;
		this->onLandBehavior = operation;
		this->buyable = isBuyable;
		this->structuresAllowed = canHaveStructures;
	}
	/**
	 * @brief Calls onLandBheavior but also could be overwritten;
	 * 
	 */
	MonopolyDecision Landable::onLand(Player* player) {
		// if (onLandBehavior != nullptr) {
			printf("You landed on : %s\n", this->name.c_str());
			MonopolyEvent event = NORMAL_LAND;

			if (this->onLandBehavior != nullptr) {

				onLandBehavior(this, player, NORMAL_LAND);
			}

			if(!this->buyable){
				//event = MonopolyEvent::TAX;
				//player->takeMoney(100);
			} else if(this->isOwned()){
				if (this->getOwner()->getID() == player->getID()) {
					event = OWNED_LAND;
					return player->notifyDecision(event);
				}
				Money total;
				if(this->structures.empty()){
					total = 50;
					player->takeMoney(total); //rent
				}
				else {
					for(int i = 0; i < this->structures.size(); i++){
						total += this->structures.at(i)->getPrice();
					}
				}
				printf("%s owns this pay him : %d\n", this->getOwner()->getName().c_str(), total);
				event = MonopolyEvent::OWNED_LAND;
			} else {
				event = MonopolyEvent::NORMAL_LAND;
			}
			return player->notifyDecision(event);

			// onLandBehavior(player, event);
		// }
	}
	/**
	 * @brief Add a structure to the vector variable
	 * 
	 * @param building 
	 */
	void Landable::addStructure(Building* building) {
		if (canHaveStructures()) {
			this->structures.push_back(building);
		}
	}
	/**
	 * @brief Purchase a structure and return if the player did or couldn't purchase.
	 * 
	 * @param player 
	 * @return true -- the building has been placed and bought
	 * @return false -- the building cannot be placed because the player doesn't have enough money or this building cannot have structures.
	 */
	bool Landable::purchaseStructure(Player* player) {
		if (!canHaveStructures()) return canHaveStructures();
		if (!player->canBuildStructure(this->color_parent))
			return false;
		if (isReadyForHotel()) {
			bool canBuy = player->takeMoney(this->houseCost);
			if (canBuy) {
				structures.clear();
				Hotel newHotel = Hotel("Hotel", hotelCost * 10);
				structures.push_back(&newHotel);
			}
			else
				return false;
		}
		else {
			bool canBuy = player->takeMoney(this->houseCost);
			if (canBuy) {
				House newHouse = House("House", houseCost);
				structures.push_back(&newHouse);
			}
			else
				return false;
		}
	}
	/**
	 * @brief Is this buyable?
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Landable::isBuyable() {
		return buyable;
	}
	/**
	 * @brief Can this have structures?
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Landable::canHaveStructures() {
		return structuresAllowed;
	}
	/**
	 * @brief Is this ready for a hotel?
	 * 
	 * @return true 
	 * @return false 
	 */
	bool Landable::isReadyForHotel() {
		return structures.size() == 4;
	}
	/**
	 * @brief return ColorID
	 * 
	 * @return PropertyColor 
	 */
	PropertyColor Landable::getColorID() {
		return color_parent;
	}

	/**
	 * @brief Construct a new Building:: Building object
	 * 
	 */
	Building::Building() : Buyable ("", 0) {

	}

	/**
	 * @brief Construct a new Building:: Building object
	 * 
	 * @param name 
	 * @param price 
	 */
	Building::Building(std::string name, Money price) : Buyable(name, price) {

	}
	/**
	 * @brief Construct a new House:: House object
	 * 
	 */
	House::House() : Building("House", 100) {

	}

	/**
	 * @brief Construct a new House:: House object, Custom Name and Price
	 * 
	 * @param name 
	 * @param price 
	 */
	House::House(std::string name, Money price) : Building(name, price){

	}

	/**
	 * @brief Construct a new Hotel:: Hotel object, with defaults
	 * 
	 */
	Hotel::Hotel() : Building("Hotel", 900) {

	}
	/**
	 * @brief Construct a new Hotel:: Hotel object, with custom name and price.
	 * 
	 * @param name 
	 * @param price 
	 */
	Hotel::Hotel(std::string name, Money price) : Building(name, price){

	}
}
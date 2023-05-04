#pragma once
#include "vector"
#include <string>
#include <functional>

namespace Monopoly {

	// enum MonopolyPlayerResponse {
	// 	//binary flags
	// 	ROLL =  1,
	// 	BUY = 2,
	// };

	enum MonopolyDecision{
		BUY = 1,
		IGNORE = 2,
		BUILD_HOUSE = 3,
	};

	enum MonopolyEvent{
		NORMAL_LAND = 0,
		OWNED_LAND = 1,
		SPECIAL_LAND = 2,
		JAIL = 4,
		TAX = 8,
	};

	using Money = unsigned int;

	struct Player;
	struct Building;



	struct MonopolyObject {
	private:
		long id;
	public:
		MonopolyObject();
		long getID();
	};

	struct Buyable : public MonopolyObject {
	private:
		Money price;
		Money sellPrice;
		bool owned, mortagaged = false;
		Player* owner;
	public:
		std::string name = "";
		Buyable(std::string name, Money price);
		Money getPrice();
		Money getSellPrice();
		bool isOwned();
		void setOwned(Player* owner);
		void setOwned(bool forced_state);
		Player* getOwner();
		void mortagageProperty();
	};


	struct PropertyColor {
	private:
		int color_id;
		int max;
	public:
		PropertyColor();
		PropertyColor(int color_id, int max);
		int getColorID();
		int getMax();
	};

	struct Landable : public Buyable {
	private:
		int spot_ID; 
		PropertyColor color_parent;
		bool buyable, structuresAllowed;
		Money houseCost, hotelCost;
		std::vector<Building*> structures = std::vector<Building*>();

	public:
		Landable();
		Landable(std::string name, Money price, bool isBuyable, bool canHaveStructures);
		Landable(std::string name, Money price, bool isBuyable, bool canHaveStructures, PropertyColor propColor);
		Landable(std::string name, Money price, bool isBuyable, bool canHaveStructures, PropertyColor propColor, std::function<void(Landable* landable, Player* player, MonopolyEvent event)> operation);
		MonopolyDecision onLand(Player* player);
		PropertyColor getColorID();
		void addStructure(Building* building);
		bool purchaseStructure(Player* player);
		std::function<void(Landable* landable, Player* player, MonopolyEvent event)> onLandBehavior;
		bool isBuyable();
		bool canHaveStructures();
		bool isReadyForHotel();
		void setLandBehavior(std::function<void(Landable* landable, Player* player, MonopolyEvent event)> behavior);
	};

	struct Jail : public Landable {
	public:
		bool buyable = false;
		Money price = 999999;
		Money sellPrice = -999999;
	};

	struct Go : public Landable {

	};

	struct CommunityChest : public Landable {

	};

	struct Chance : public Landable {

	};

	struct Building : public Buyable {
	public:
		Building();
		Building(std::string name, Money price);

	};

	struct House : public Building {
	public:
		House();
		House(std::string name, Money price);
	};

	struct Hotel : public Building {
	public:
		Hotel();
		Hotel(std::string name, Money price);
	};




	struct Player : public MonopolyObject {
	private:
		std::string name;
		Money money;
		std::vector<Landable*> ownedProperties = std::vector<Landable*>();
		bool isInJail;
		int position = 0;
	public:
		Player();
		Player(std::string name, Money startingMoney);

		Money addMoney(Money new_cash);
		bool canBuildStructure(PropertyColor color_id);
		bool buyProperty(Landable* property);
		bool addProperty(Landable* property);
		bool takeMoney(Money debt);
		void setMoney(Money cash);
		void setInJail(bool inJail);
		bool inJail();
		void setPosition(int position);
		int getPosition();
		void notifyTurn();
		MonopolyDecision notifyDecision(MonopolyEvent event);
		std::string getName();

		

	};

}
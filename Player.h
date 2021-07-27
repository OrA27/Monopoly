#pragma once
#include "Asset.h"
#include "Instruction.h"
#include <vector>	 // used for the array of assets owned by the player
#include "Deck.h"	 // used for pulling cards
#include <algorithm> //used to find and calculate player location
// #include <cmath>  //included deck.h


#define PLAYER "in class-Player "
//#define DOUBLE

class Asset;

class Player
{
	string p_name;
	int balance;
	Slot* location;
	vector<Asset*> owned;
	bool in_jail;

public:
	Player(string name, Slot* start); // constructor - tested
	Player(const Player& other); // copy constructor, uses operator= - tested
	~Player(); //destructor - tested 
	Player& operator=(const Player& other); // operator= , prevents copying - tested
	void setName(const string& name); // sets the name, only used during construction - tested
	void setLoc(Slot* loc); // sets the location of the player when out of scope - tested
	void setBalance(int b); // sets the balance of the player when out of scope - tested
	string getName()const {return p_name; } // gets name of player - tested
	Slot* getLoc() const { return location; } // gets location of player - tested
	bool changeBalance(int change); // changes the balance of the player
									// per the rules given by the assignment - tested
	void payMortgage(Asset& prprty, int payout); // pays the mortgage of an asset - tested
	bool pawn(int change); // pawns an asset - tested
	void buyProperty(Asset& prprty); // player buys a property - tested
	void quit(); // player quits the game (whether by choice or by loss) - tested
	void move(vector<Slot*>& the_board); // moving logic of player - tested
	void increaseMortgage(); // increases mortgage of all pawned assets owned by player
	void printLoc(int idx) const; // prints the location of a player
	bool asset(); // game logic when player lands on Asset tile
	bool instruct(Deck& deck); // game logic when player lands on Instruction tile
	bool isInJail(); // check if players in jail and frees from jail if true
	bool getTicket(Deck& deck); // player pulls a ticket from deck and get/loses money
	void printStatus(); // prints status of the player
};


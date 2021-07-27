#pragma once

#include "Asset.h"
#include "Instruction.h"
#include "Player.h"
#include "Deck.h"
#include <fstream>	// used to read from the file
#include <typeinfo> // used to distinguish content of Slot* objects
#include <list>		// used to contain the player
// #include <iostream> // included in Slot which is included in Asset.h\instruction.h\Player.h
// #include <queue> // included in Deck.h

using namespace std;

#define FILE_ERR "could not open file "
#define VEC_ERR "vector error "
#define GE "in class-gameEngine "
#define ALLOWANCE 350 //initial amount of money
#define TURN_LINE cout << "--------------------------------------------" << endl // separates turns
#define SPACE cout << endl


class GameEngine
{
	vector<Slot*> board;
	list<Player*> players;
	Deck deck;

public:
	GameEngine(string path, int player_num); //constructor - tested
	GameEngine(const GameEngine& other); // copy - tested
	GameEngine& operator=(const GameEngine& other); // copy - tested
	~GameEngine(); //destructor - tested
	void createBoard(string path); // reads from a file and creates a board - tested
	void createPlayers(int player_num); // creates a list of player - tested
	Slot* readData(string data); // reads the data and creates the appropriate slot - tested
	void parser(vector<string>& parsed, string data); // parses a string into a vector of data - tested
	void GameON(); // game loop - tested
	bool turn(Player& player); // turn of a player
	bool activateSlot(Player& player); // activate the slot logic

#ifdef DEBUG
	void test(); // used for testing singular method independently
#endif // DEBUG
};


#include "GameEngine.h"


/// <summary>
/// constructs Game Engine
/// </summary>
/// <param name="path">path to text file that holds board data</param>
/// <param name="player_num">desired amount of players</param>
GameEngine::GameEngine(string path, int player_num)
{
	// board construction
	this->createBoard(path);
	// players construction
	this->createPlayers(player_num);
	// deck construction happens automatically
}

/// <summary>
/// copying constructor uses operator=
/// which prevents copying
/// </summary>
/// <param name="other"></param>
GameEngine::GameEngine(const GameEngine& other)
{
	*this = other;
}

/// <summary>
/// prevents from copying through operator=
/// extra layer of protection after "init" value in Deck
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
GameEngine& GameEngine::operator=(const GameEngine& other)
{
	throw COPY GE;
}

/// <summary>
/// destructor for GameEngine
/// </summary>
GameEngine::~GameEngine()
{
	vector<Slot*>::iterator b_it;
	list<Player*>::iterator p_it;
	for (b_it = this->board.begin(); b_it != this->board.end(); b_it++) // go over board elements
	{
		delete (*b_it); // delete/free the content of the element
	}
	this->board.clear(); //clears the vector (frees the addresses of the pointer themselves)
	for (p_it = this->players.begin(); p_it != this->players.end(); p_it++) // go over players list
	{
		delete (*p_it); // delete/free the content of the element
	}
	this->players.clear(); //clear the list (frees the addresses of the pointer themselves)
}

/// <summary>
/// set method for 'board'
/// </summary>
/// <param name="path">path to text file that holds board data</param>
/// <returns>void</returns>
void GameEngine::createBoard(string path) throw(string)
// check if a starting slot sorting function is needed
{
	ifstream board_file;
	board_file.open(path, ios::in); // open file only if it exists
	if (!(board_file.is_open())) { throw FILE_ERR GE  "createBoard"; } //throw error just in case
	board_file.seekg(0, ios::beg); // ensures the reading is from the start
	char line_data[50]; // line data is stored here
	while (board_file.getline(line_data, 50)) //as long as it keeps getting lines
	{
		board.push_back(this->readData(line_data)); // add tile (through parsing) into board
	}
	board_file.close(); // close file
}

/// <summary>
/// set method for 'players'
/// </summary>
/// <param name="player_num">desired amount of players</param>
void GameEngine::createPlayers(int player_num) throw(string)
// count 7 lines in this function -> starting slot sorting(?)
{
	if (player_num <= 1 || player_num > 6) { throw VALUE GE "createPlayers"; }
	Player* player = nullptr;
	for (int i = 0; i < player_num; i++)
	{
#ifndef DEBUG
		char name[50]; //exists only within loop scope
		cout << "enter player " << i + 1 << " name" << endl;
		cin.ignore(cin.rdbuf()->in_avail()); // make sure \n is not part of the buffer
		cin.getline(name, 50); // get the name of the player
#else
		char name[9] = "Player #"; // a set name for all players
		memset(name + 7, i + 49, sizeof(char)); // players are distinguished by numbers
#endif // !DEBUG
		if (name == "" || name == "\n") { throw STRING GE "createPlayers"; }
		player = new Player(name, *this->board.begin()); // construct player
		player->setBalance(ALLOWANCE); // set the initial money for the player
		this->players.push_back(player); //add player to the game
		player = nullptr; //reset pointer
	}
}

/// <summary>
/// converts a string into a 'Slot*' object
/// </summary>
/// <param name="data">contains all data needed for the string</param>
/// <returns>Slot*</returns>
Slot* GameEngine::readData(string data) throw(string)
{

	vector<string> parsed;
	this->parser(parsed, data); //turn the string into a vector

	if (parsed[0] == "I") // instruction type slot
	{
		if (parsed[1].length() != 1) { throw STRING GE "readData"; } // first member is always a single character
		char type = parsed[1][0]; // copy the character into an array to emulate a string object
		if (parsed.size() != 3) { throw VALUE GE "readData"; } // I type lines are always 3 elements long
		Instruction* tile = new Instruction(type, parsed[2]); // create an Instruction slot
		return tile;
	}
	else if (parsed[0] == "P") // instruction type slot
	{
		if (parsed.size() != 5) { throw VALUE GE "readData"; } // P type lines are always 5 elements long
		Asset* tile = new Asset(parsed[1], parsed[2], stoi(parsed[3]), stoi(parsed[4])); // create an Asset slot
		return tile;
	}
	else { throw STRING GE " readData"; } // used mostly for testing

}

/// <summary>
/// parses a string into a vector
/// </summary>
/// <param name="parsed">reference to a vector that will contain the data</param>
/// <param name="data">string that needs to be parsed</param>
void GameEngine::parser(vector<string>& parsed, string data) throw(string)
{
	
	if (!parsed.empty()) { throw VEC_ERR GE "parser"; }
	if (data == "") { throw STRING GE "parser"; }
	string piece;
	size_t pos = 0; // set position indicator
	while (pos != data.npos) //as long as the first is not end of string
	{
		pos = data.find_first_of(','); // set as pos to next delimiter 
		piece = data.substr(0, pos); // isolate substring
		parsed.push_back(piece); // insert the substring to the vector
		data = data.substr(pos + 1, data.npos); //remainder of string
	}
}

/// <summary>
/// main game loop
/// </summary>
void GameEngine::GameON()
{
	bool in_game = true;
	bool choice = false;
	list<Player*>::iterator p_it = this->players.begin();

	// run as long as there is more than one player
	while (this->players.begin() != prev(this->players.end()))
	{
		// if we reached the end of the list, return to its beginning
		if (p_it == this->players.end()) { p_it = this->players.begin(); }
		
		
		TURN_LINE;
		cout << "it's " << (*p_it)->getName() << "'s turn" << endl; //state player turn
		(*p_it)->printStatus(); //print player data
		SPACE;

		
#ifndef DEBUG
		//ask if they want to quit
		cout << "would you like to quit? (yes=1:no=0) " << endl;
		cin >> choice;
#else
		choice = false;
#endif // !DEBUG

		
		if (choice) //delete contents of player inside quit
		{
			cout << (*p_it)->getName() << " withdrew from the game";
			(*p_it)->quit();
			delete* p_it; // delete content of iterator
			p_it = this->players.erase(p_it); // remove the pointer from the list (effectively deleting it)
			SPACE;
			continue; //continue
		}

		SPACE;

		if ((*p_it)->isInJail())  // check if player is in jail
		{
			p_it++; // go to next player
			SPACE;
			continue;
		}
		
		in_game = this->turn((**p_it)); // turn logic

		if (!in_game) // if player still has less than 0 NIS (with 0 player is still in game)
		{
			cout << (*p_it)->getName() << " has lost" << endl;
			(*p_it)->quit();
			delete* p_it;
			p_it = this->players.erase(p_it);
			SPACE;
			continue;
		} // turn logic returned false so player is out

		p_it++; // go to next player
		SPACE;
	}
	//there is only 1 player and therefore they are the winner
	cout << "CONGRATULATIONS " << (*players.begin())->getName() << " is the WINNER!!" << endl;
	cout << endl << "It's time to pack up the game, lets go!" << endl;
	// announce the winner
}

/// <summary>
/// turn logic
/// </summary>
/// <param name="player">current player</param>
bool GameEngine::turn(Player& player)
{
	player.move(this->board); // moving logic
	SPACE;
	return this->activateSlot(player); // slot logic
}

/// <summary>
/// activates the slot that the player landed on
/// </summary>
/// <param name="player"> current player</param>
bool GameEngine::activateSlot(Player& player) throw(string)
{
	
	Slot* tile = player.getLoc(); // invoke getLoc method once and store its data

	if (typeid(*tile) == typeid(Asset)) // if the slot is an Asset
	{
		return player.asset(); // activate asset logic
	}
	else if (typeid(*tile) == typeid(Instruction)) // if the slot is an Instruction
	{
		 return player.instruct(deck); // activate instruction logic
	}
	else { throw D_VALUE GE "activeSlot"; } // anything else is an exception
}

#ifdef DEBUG
/// <summary>
/// tests a single method with no effects from other methods
/// </summary>
void GameEngine::test()
{
}
#endif // DEBUG

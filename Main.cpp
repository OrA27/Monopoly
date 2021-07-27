//no need to include Slot.h since it's already in asset.h and instruction.h which are in gameEngine.h
#include <ctime> //used to set the seed
#include "GameEngine.h"

/*
* manual:

* MODES:
* * DEBUG MODE-
* * * you can activate this mode by defining DEBUG constant in Slot.h
* * * it will set the players number and the path in advance
* * * and remove the need to make any choices
* * * i.e players never quit and always attempt to buy a property

* * DOUBLE MONEY MODE-
* * * players get double money if they land on Starting tile
* * * you can activate this mode by defining DOUBLE constant ins Player.h

* RULES:
* * LOSS-
* * * players will lose only if they have less than 0 NIS
* * * and no assets left to pawn (if there are any)

* ASSIGNMENT REQUESTS:
* * SKIPPING PARTS-
* * * no parts were skipped, all methods and requests have been fulfilled

* * EXCEPTIONS-
* * * there are myriad of exceptions, all of them are important

* * COMMENTS-
* * * the entire project is commented

* * STL-
* * * there are 3 different uses of STL: queue, vector and list
* * * the Deck is a class that contains a queue
* * * the container of players in GameEngine
* * * there are multiple uses of vectors through out the code:
* * *	* the board is accessed through a vector
* * *	* the assets owned by the player is accessed through a vector

* * INHERTIANCE-
* * * Asset and Instruction classes are both derived from Slot class.
* * * Slot Class is an abstract class that a myriad of pure/virtual methods

* * TYPE_INFO-
* * * there is a use of "typeid()" method within the
* * * "activateSlot" method in class GameEngine
*/

void main()
{
	srand(time(NULL));
	try
	{
		int players = 3;
		char path[128]
#ifdef DEBUG
			= "board.txt";
#else
			;
		cout << "enter the path to the game board file:" << endl;
		cin.getline(path, 128);
		cout << "enter how many players are participating: (number between 2-6)" << endl;
		cin >> players;
#endif // DEBUG
		GameEngine game(path, players);
		game.GameON();
	}

	catch (const char* ex)
	{
		cout << ex << ", game is terminated" << endl;
	}
	catch (...)
	{
		cout << "Unknown error happened, you would think that" <<
			" with all those exceptions we would have caught them all D:" << endl;
	}
}
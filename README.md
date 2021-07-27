# Monopoly
A game of monopoly made as a final project for c++ course.
The game has no UI and is played on thorugh the command console,
in order for the exe file to work correctly it has to have the Board.txt file in the same folder.

the code is divided into multiple .h and .cpp files, each has their corresponding name.
the manual for the game is included below (and in the Main.cpp file) for your convenience.

# manual
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

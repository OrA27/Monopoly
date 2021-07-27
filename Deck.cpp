#include "Deck.h"


bool Deck::init = false;

/// <summary>
/// constructor for deck
/// </summary>
Deck::Deck() 
{
	this->initialize();
}
/// <summary>
/// initialize a single deck and prevents
/// creation of any other instances
/// </summary>
void Deck::initialize()throw(string)
{
	if (!this->init)
	{
		this->init = true; // prevents any creation of other Deck instances
						   // and in addition also prevents creation of additional GameEngine instances
		createDeck();
	}
	else { throw INIT; }
}

/// <summary>
/// prevents copying of other deck
/// </summary>
/// <param name="deck:">the deck to be copied</param>
/// <returns>exception</returns>
Deck& Deck::operator=(const Deck& deck)
{
	throw D_COPY DCK;
}

/// <summary>
/// uses operator= that prevents copying
/// </summary>
/// <param name="deck">the deck to be copied</param>
Deck::Deck(const Deck& deck) // will call operator= which will throw exception
{
	*this = deck;
}


/// <summary>
/// set method for the Deck
/// </summary>
void Deck::createDeck()
{
	for (int i = 0; i < N; i++)
	{
		int randnum = (rand() % BORDER + 1); // get random number between 1 and BORDER
		randnum *= pow((-1), rand() % 2); // make some cards be negative
		money.push(randnum); // enter randnum to deck
	}
}

/// <summary>
/// pulls a card from top of the deck
/// then returns it to the bottom of the deck
/// </summary>
/// <returns>int</returns>
int Deck::pullCard()
{
	const int val = this->money.front(); //get the value of the front card
	this->money.pop(); // pop it from the top
	this->money.push(val); // insert it back to the end of the queue

	return val;
}

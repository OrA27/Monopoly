#pragma once
#include <string>
#include <cmath> // used for card creation
#include <queue> // used for the deck itself

using namespace std;

#define D_VALUE "invalid value entered "
#define INIT "there is already a deck\GameEngine in place "
#define D_COPY "can not use copy "
#define DCK "in class Deck "
#define BORDER  350	// the limit (both positive and negative) of money value
#define N 20		// number of cards to create;

class Deck
{
	queue<int> money;

public:
	static bool init;
	Deck();
	void initialize();
	Deck& operator=(const Deck& deck);
	Deck(const Deck& deck);
	void createDeck();
	int pullCard();
};

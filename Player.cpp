#include "Player.h"

/// <summary>
/// constructs player object
/// </summary>
/// <param name="name">name of player</param>
/// <param name="start">starting position of player</param>
Player::Player(string name, Slot* start)
{
	this->setName(name);
	balance = 0;
	this->setLoc(start);
	in_jail = false;
}

/// <summary>
/// copying constructor for player
/// </summary>
/// <param name=""></param>
Player::Player(const Player& other)
{
	*this = other;
}
	
/// <summary>
/// destructor for player
/// </summary>
Player::~Player()
{
#ifdef DEBUG
	cout << this->p_name << " was removed from the game" << endl;
	p_name = "";
	balance = 0;
	location = nullptr;
#endif // DEBUG
}

Player& Player::operator=(const Player& other)
{
	throw COPY PLAYER;
}

/// <summary>
/// sets the name of the player
/// </summary>
/// <param name="name">name of player</param>
/// <returns>void</returns>
void Player::setName(const string& name) throw(string)
{
	if (name == "") { throw STRING PLAYER "setName"; }
	p_name = name;
}


/// <summary>
/// sets the player's location on the slots
/// </summary>
/// <param name="local">slot the player will step into</param>
/// <returns>void</returns>
void Player::setLoc(Slot* local) throw(string)
{
	if (&local == nullptr) { throw ADDRESS PLAYER "setLoc"; }
	location = local;
}

/// <summary>
/// sets the balance of the player to a fixed number
/// </summary>
/// <param name="b">amount of money in player's balance</param>
/// <returns>void</returns>
void Player::setBalance(int b)
{
	// no need for (b < 0) Error since it indicates a loss
	balance = b;
}

/// <summary>
/// changes the balance of the player
/// and place properties of it in or out of mortgages
/// depending on the value
/// </summary>
/// <param name="change">amount of money to be added\subtracted</param>
/// <returns>bool</returns>
bool Player::changeBalance(int change) throw(string)
{
	if (change > 0)
	{
		cout << this->getName() << " received " << change << " NIS" << endl;
		this->setBalance(this->balance + change); // adds the change to balance
		vector<Asset*>::iterator iter; // create an appropriate iterator
		int payout = 0;
		for (iter = owned.begin(); iter != owned.end(); iter++) // go over asset vector
		{
			//calculate the amount of money needed to pay the mortgage
			payout = round((*iter)->getMortgage() * INTEREST * (*iter)->getPPrice());
			if (payout > 0 && this->balance > payout) // check if it's possible to pay it
			{
				this->payMortgage(**iter, payout);
			}
		}
		cout << this->getName() << " now has " << this->balance << " NIS" << endl;
		return true;
	}
	else if (change < 0) { return pawn(change); } // if player needs to be charged go to pawn method
	else { return true; } // value is 0 and therefor invalid
}

/// <summary>
/// Player pays out mortgage of specific Asset he owns
/// </summary>
/// <param name="prprty">the asset player is paying out</param>
/// <param name="payout">the amount of money needs to be payed</param>
/// <returns>void</returns> 
void Player::payMortgage(Asset& prprty, int payout)
{
	if (prprty.getOwner() != this) { throw MIX PLAYER "in payMortgage"; } // asset owner is not current player
	this->setBalance(this->balance - payout); // pay the mortgage
	prprty.setMortgage(0); // remove mortgage from asset
	cout << prprty.getMainName() << " at " << prprty.getName() << " mortgage has been paid" << endl;
}

/// <summary>
/// pawns player buildings until it can pay the change
/// </summary>
/// <param name="change">the amount of money needs to be payed</param>
/// <returns>bool</returns>
bool Player::pawn(int change)
{
	vector<Asset*>::iterator iter; // appropriate iterator
	//loop as long as iterator has not reached the end and balance is not enough for the change
	cout << this->getName() << " needs to pay " << -1 * change << " NIS" << endl;

	for (iter = owned.begin(); iter != owned.end() && this->balance < abs(change); iter++)
	{
		if ((*iter)->getMortgage() == 0) // check if house is not mortgaged
		{
			(*iter)->setMortgage(1); // pawn the house
			this->setBalance(this->balance + (*iter)->getPPrice()); // give player some money
			//notify of asset being pawned
			cout << (*iter)->getMainName() << " at " << (*iter)->getName()
				<< " has been pawned due to lack of funds" << endl;
		}

	}

	if (this->balance > abs(change)) // check in case all assets have been pawned
	{
		this->setBalance(this->balance + change); // remove change (which is negative) from balance
		cout << this->getName() << " now has " << this->balance << " NIS left" << endl;
		return true;
	}
	cout << "sadly, " << this->getName() << " has no money and no Active Assets left" << endl;
	return false;
}
/// <summary>
/// set an Asset as owned by the player
/// and adds it to the player owned Assets
/// </summary>
/// <param name="prprty">the asset to be bought\owned</param>
void Player::buyProperty(Asset& prprty)
{
	int price = prprty.getPPrice();
	if (this->balance >= price) // player can afford asset
	{
		this->setBalance(this->balance - price); // pay for it
		prprty.setOwner(*this); // set player as owner
		this->owned.push_back(&prprty); // add asset to owned vector
		cout << this->getName() << " successfully bought the property for "
			<< price << " NIS and now has " << this->balance << " NIS left" << endl;
	}
	else // player can't afford
	{
		cout << this->getName() << " could not buy the property - not enough money" << endl; //notify player
	}

}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
void Player::quit()
{
	vector<Asset*>::iterator it;
	for (it = this->owned.begin(); it != this->owned.end(); it++) // go over owned assets
	{
		(*it)->release(); // releases them from player
	}
	this->owned.clear(); // clears owned asset vector
}

/// <summary>
/// moving logic of a player
/// </summary>
/// <param name="the_board">give access to the board of the game</param>
void Player::move(vector<Slot*>& the_board)
{
	int dice = 1, i = 0;
	//set iterator to current location of player
	vector<Slot*>::iterator it = find(the_board.begin(),the_board.end(),this->location);
	int idx_e, idx_s = distance(the_board.begin(), it); //get index of location on board
	this->printLoc(idx_s); // print location
	dice = (rand() % 6) + 1; // roll a number between 1-6
	cout << this->p_name << " rolled a " << dice << endl; // notify dice value
	it = the_board.begin() + ((idx_s + dice) % the_board.size()); // update location
	if (idx_s > (idx_e = distance(the_board.begin(), it))) // check if completed a full circle
	{
		this->changeBalance(BASE); // add 350 to player balance
		this->increaseMortgage(); // self explanatory
	}
	this->location = *it; // set new location of player
	this->printLoc(idx_e); // print new location of player
	


}

/// <summary>
/// increases mortgage on all pawned assets of the player
/// </summary>
void Player::increaseMortgage()
{
	vector<Asset*>::iterator a_it;
	int mort; // int to call the getMortgage function n times and not 2n times
	for (a_it = owned.begin(); a_it != owned.end(); a_it++) // go over player assets
	{
		mort = (*a_it)->getMortgage(); // self explanatory
		if (mort > 0) // if mortgage is over 0
		{
			(*a_it)->setMortgage(mort + 1); //increases mortgage by 1
		}
	}
}

/// <summary>
/// prints location of player
/// </summary>
/// <param name="idx">index of location on the board vector</param>
void Player::printLoc(int idx) const
{
	cout << this->p_name <<" is on slot No." << idx + 1 << " "; // idx is increased by 1 because it starts from 0
	this->location->print(); // print location data
	cout << endl;
}

/// <summary>
/// logic of asset tiles
/// </summary>
/// <returns>bool</returns>
bool Player::asset()
{
	Asset* tile = static_cast<Asset*>(this->location);
	bool opt = false;
	if (!tile->getOwner()) // if asset has no owner
	{
#ifndef DEBUG
		cout << "would you like to buy it for "
			<< tile->getPPrice() <<"? (yes=1:no=0)" << endl;
		cin >> opt;
#else
		opt = true;
#endif
		if (opt) { this->buyProperty(*tile); } // attempt to buy the house;
		return true;
	}
	else if(tile->getOwner() != this)
	{
		cout << "''hi " << this->p_name << " enjoy your stay in our humble estate''"<< endl;
		int rent = tile->getRPrice(); // get the rent price of the asset
		opt = this->changeBalance(-1 * rent); // player tries to pay
		if (tile->getMortgage()) { return opt; } // if house is pawned just return result of opt
		if (!opt) { rent = this->balance; } // if player failed to pay full sum
											// it pays with the everything it has
		tile->getOwner()->changeBalance(rent); // owner of asset gets payed
		return opt; // return result of opt
	}
	else
	{
		cout << this->p_name << " stopped for a drink in their property" << endl;
		return true;
	}
}

/// <summary>
/// logic of instruction tiles
/// </summary>
/// <returns>bool</returns>
bool Player::instruct(Deck& deck) throw(string)
{
	Instruction* tile = static_cast<Instruction*>(this->location);
	//char type = tile->getType();
	switch (tile->getType())
	{
	case 'T': // instruction is type T
		cout << this->p_name << " takes a card from the deck" << endl;
		return this->getTicket(deck); // get a ticket and follow its value
	case 'J': // instruction is type J
		cout << this->p_name << " has been arrested during a visit at the county jail" << endl;
		this->in_jail = true; // put player into jail
		return true;
	case 'S': // instruction is type s
		// IMPORTANT we were not told what to do in this case
		// we took the liberty to follow Monopoly rules
		// and double the player starting money (adding another 350 to player)
		// this option can be activated by enabling the DOUBLE constant in Instruction.h
#ifdef DOUBLE
		cout << "well, well, well... it seems " << this->p_name
			<< " is in luck and receives extra cash" << endl;
		return changeBalance(BASE); // always returns true
#else
		return true;
#endif // DDUBLE

		

	default:
		throw VALUE PLAYER "instruct"; // used for testing
	}
}

/// <summary>
/// checks if player's in jail
/// and releases if necessary 
/// </summary>
/// <returns>bool</returns>
bool Player::isInJail()
{
	if (this->in_jail) // if player's in jail
	{
		cout << this->p_name << " is in jail and can't move this turn :(" << endl;
		in_jail = false; // change status
		return true;
	}
	return false;
}

/// <summary>
/// pulls a card from deck
/// and changes balance accordingly
/// </summary>
/// <param name="deck">deck to pull cards from</param>
/// <returns></returns>
bool Player::getTicket(Deck& deck)
{
	return this->changeBalance(deck.pullCard());
}

/// <summary>
/// prints the status of the player
/// not const because it uses an iterator
/// </summary>
void Player::printStatus()
{
	cout << "they have " << this->balance << " NIS" << endl;
	if (this->owned.size())
	{
		cout << "and own the following assets:" << endl;
		vector<Asset*>::iterator it;
		for (it = this->owned.begin(); it != this->owned.end(); it++)
		{
			int m = (*it)->getMortgage();
			cout << (**it) << (m ? " pawned" : " active") << endl;
		}
	}
	else { cout << "and have no assets" << endl; }
}


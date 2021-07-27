#pragma once
#include "Slot.h"
#include "Player.h"

#define AST "in class-Asset "
#define MIX "invalid ownership access "

#define INTEREST 1.3 // interest rate is fixed through the whole game
                     // therefore it would be a constant
                     // were we asked to change the interest rate
                     // we would have set it as a static variable

class Player;

class Asset :
    public Slot
{
    string city_name;
    Player* owner;
    int property_price;
    int rent;
    int mortgage;

public:
    
    Asset(string c_name, string m_name, int p, int r); // constructor for Asset - tested
    ~Asset(); // destructor for Asset - tested
    Slot& operator=(const Slot& other); // throws exception whenever it's attempted
    void setName(const string& name); // sets the name of the city group, only used in constructor 
                                      // throws exception if string is empty - tested
    void setOwner(Player& buyer); // sets owner of an asset, used when needed to be changed out of scope - tested
    void setPPrice(int p); // sets the buying price of an asset, throws exception if it's below 0 - tested
    void setRPrice(int r); // sets the renting price of an asset, throws exception if it's below 0 - tested
    void setMortgage(int m); // sets the mortgage, used when out of scope - tested
    void print() const; // virtual indirection to operator << - tested
    string getName() const { return city_name; } // gets the name of the city when out of scope - tested
    Player* getOwner() const { return owner; } // gets owner when out of scope - tested
    int getPPrice() const { return property_price; } // gets buying price - tested
    int getRPrice() const { return rent; } // gets renting price - tested
    int getMortgage() const { return mortgage; } // gets mortgage years - tested
    friend ostream& operator<<(ostream& out, const Asset& ast); // overloaded operator << for asset -tested
    void release(); // frees asset out of owner - tested
};


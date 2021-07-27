#pragma once

#include <string>
#include <iostream>
#include <iomanip> //although not used here, it's used in both of the derived classes

using namespace std;

#define ADDRESS "variable has invalid address "
#define STRING "Empty or invalid string "
#define VALUE "invalid value "
#define SLOT "in class-Slot "
#define COPY "can not use copy constructor "
//#define DEBUG

class Slot
{
protected:
	string main_name;
public:
	Slot(const string& name); // constructor for slot - tested
	Slot(const Slot& other); // copying constructor for slot that contains operator=
	virtual ~Slot(); // virtual destructor to ensure proper destruction of derived classes - tested
	virtual Slot& operator=(const Slot& other)=0; // pure virtual operator, only derived classes use this - tested  
	void setName(const string& name); // sets the main_name of the Slot - tested
	virtual void print() const = 0; // pure virtual print, only derived classes use this - tested
	string getMainName() const { return main_name; } // gets the main_name of the slot
													 // in case its needed from out of scope - tested
	
};


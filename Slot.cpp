#include "Slot.h"
/// <summary>
/// constructs Slot object
/// </summary>
/// <param name="name">main name of the slot</param>
Slot::Slot(const string& name)
{
	this->setName(name);
}
Slot::Slot(const Slot& other)
{
	*this = other;
}

/// <summary>
/// virtual destructor for Slot
/// </summary>
Slot::~Slot()
{
#ifdef DEBUG
	cout << "slot removed entirely" << endl;
#endif
}

/// <summary>
/// sets the name of a slot object
/// </summary>
/// <param name="name">main name of the slot</param>
void Slot::setName(const string& name)
{
	if (name == "") { throw STRING SLOT "setName"; }
	main_name = name;
}

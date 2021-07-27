#include "Asset.h"


/// <summary>
/// constructs Asset object
/// </summary>
/// <param name="c_name">name of the city</param>
/// <param name="m_name">main name of slot</param>
/// <param name="p">price of property</param>
/// <param name="r">renting price</param>
Asset::Asset(string c_name, string m_name, int p, int r)
	:Slot(m_name)
{
	this->setName(c_name);
	owner = nullptr;
	this->setPPrice(p);
	this->setRPrice(r);
	this->setMortgage(0);
}

/// <summary>
/// destructor for asset
/// there are no dynamic memory allocated fields
/// therefor it only sends notification in DEBUG mode
/// </summary>
Asset::~Asset()
{
#ifdef DEBUG
	cout << this->main_name << " in " << this->city_name << " has been destroyed " << endl;
#endif
}

/// <summary>
/// throws exception when attempted
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Slot& Asset::operator=(const Slot& other)
{
	throw COPY AST;
}

/// <summary>
/// sets name of Asset
/// </summary>
/// <param name="name">name of city</param>
/// <returns></returns>
void Asset::setName(const string& name) throw(string)
{
	if (name == "") { throw STRING AST "setName"; }
	city_name = name;
}

/// <summary>
/// sets owner of Asset
/// </summary>
/// <param name="buyer">name of the new owner</param>
void Asset::setOwner(Player& buyer)
{
	if (owner) { throw MIX AST "setOwner"; }
	owner = &buyer;
}

/// <summary>
/// sets the Asset's property price
/// </summary>
/// <param name="p">property price</param>
void Asset::setPPrice(int p)
{
	if (p < 0) { throw VALUE AST "setPPrice"; }
	property_price = p;
}

/// <summary>
/// sets renting price of Asset
/// </summary>
/// <param name="r">Asset</param>
void Asset::setRPrice(int r)
{
	if (r < 0) { throw VALUE AST "setRPrice"; }
	rent = r;
}


/// <summary>
/// sets the years of mortgage left to pay
/// </summary>
/// <param name="m">number of years left</param>
/// <returns></returns>
void Asset::setMortgage(int m) throw(string)
{
	if (m < 0) { throw VALUE AST "setMortgage"; }
	mortgage = m;
}

/// <summary>
/// indirection to << operator
/// </summary>
void Asset::print() const
{
	cout << *this;
}

/// <summary>
/// frees asset of owner
/// </summary>
void Asset::release()
{
	this->owner = nullptr;
	this->setMortgage(NULL);
}


/// <summary>
/// operator << for Asset
/// </summary>
/// <param name="out">buffer</param>
/// <param name="ast">object to be printed</param>
/// <returns></returns>
ostream& operator<<(ostream& out, const Asset& ast)
{
	Player* ownr = ast.getOwner();
	out << left
		<< setw(12) << setfill(' ') << ast.main_name //property name
		<< setw(12) << setfill(' ') << ast.city_name //city name
		<< setw(12) << setfill(' ') << (ownr ? ownr->getName() : "no owner ");// //owner name
	  //the part below is unnecessary since it was not requested
	  /*
	    << setw(12) << setfill(' ') << ast.property_price
		<< setw(12) << setfill(' ') << ast.rent
		<< setw(12) << setfill(' ') << ast.mortgage;
	  */
	return out;
}

#include "Instruction.h"

/// <summary>
/// constructs an Instruction class object
/// </summary>
/// <param name="m_name">main name of slot</param>
/// <param name="t_name">type of instruction</param>
/// <param name="desc">description of instruction</param>
Instruction::Instruction(char t_name, string m_name)
	:Slot(m_name)
{
	this->setType(t_name);
}

/// <summary>
/// operator= for class
/// has the purpose of preventing copying
/// </summary>
/// <param name="other"> the other object of the class</param>
/// <returns>Instruction&</returns>
Slot& Instruction::operator=(const Slot& other)
{
	throw COPY INST;
}

Instruction::~Instruction()
{
#ifdef DEBUG
	cout << this->main_name << " of type " << this->type << " has been destroyed " << endl;
#endif // DEBUG

}

/// <summary>
/// sets the type field of the Instruction
/// </summary>
/// <param name="i_type">type of instruction</param>
/// <returns></returns>
void Instruction::setType(const char& i_type) throw(string)
{
	if ( (i_type != 'S') && (i_type != 'T') && (i_type != 'J') )
		throw STRING INST "setType";

	type = i_type;
}

/// <summary>
/// indirection to operator <<
/// </summary>
void Instruction::print() const
{
	cout << *this;
}

/// <summary>
/// prints out the details of the instruction
/// </summary>
/// <param name="out">- the buffer to be printed</param>
/// <param name="inst">- the object to be printed</param>
/// <returns>ostream&</returns>
ostream& operator<<(ostream& out, const Instruction& inst)
{
	out << left
		<< setw(0) << inst.getType() << "- "
		<< setw(10) << inst.getMainName() << " ";

	return out;
}

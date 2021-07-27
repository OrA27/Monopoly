#pragma once
#include "Slot.h"


#define INST "in class-Instruction "
#define BASE 350 //the amount of money received upon walking on or through S type instruction
//#define DOUBLE //if player steps on S tile they get double money

class Instruction :
    public Slot
{
    char type;

public:
    Instruction(char t_name, string m_name); //tested
    Slot& operator=(const Slot& other);
    ~Instruction();
    void setType(const char& i_type); //tested
    char getType() const { return type; } //tested
    void print() const; //tested
    friend ostream& operator<<(ostream& out, const Instruction& inst); //tested
};
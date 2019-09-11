#include "Operands.hpp"
#include "IOperand.hpp"
#include "Functions.hpp"

Operands::Operands()
{
	operands[_Int8] = &Operands::createInt8;
	operands[_Int16] = &Operands::createInt16;
	operands[_Int32] = &Operands::createInt32;
	operands[_Float] = &Operands::createFloat;
	operands[_Double] = &Operands::createDouble;
}

Operands::~Operands(){};

IOperand const * Operands::createOperand(eOperandType type, std::string const &value) const
{
	IOperand const *(Operands::*operand)(std::string  const &value) const;
	operand = operands.at(type);
	return((this->*operand)(value));
}

 IOperand const * Operands::createInt8( std::string const & value) const
 {
	 return new Functions<int8_t>(value, _Int8);
 }

 IOperand const * Operands::createInt16( std::string const & value) const
 {
	 return new Functions<int16_t>(value, _Int16);
 }

 IOperand const * Operands::createInt32( std::string const & value) const
 {
	 return new Functions<int32_t>(value, _Int32);
 }

 IOperand const * Operands::createFloat( std::string const & value) const
 {
	 return new Functions<float_t>(value, _Float);
 }

 IOperand const * Operands::createDouble( std::string const & value) const
 {
	 return new Functions<double_t>(value, _Double);
 }
 

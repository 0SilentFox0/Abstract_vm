#ifndef OPERANDS_HPP
#define OPERANDS_HPP

# include "IOperand.hpp"

class Operands
{
	public:
		Operands();
		Operands(const Operands&);
		const Operands& operator=(const Operands&);
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		~Operands();

	private:
		std::map<eOperandType, IOperand const *(Operands::*)(std::string const & value) const> operands;

		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
};
#endif
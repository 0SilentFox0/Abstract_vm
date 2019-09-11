#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Operands.hpp"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define FINISH "\033[0m"
#define YEL "\033[33m"

class Commands
{

public:
	Commands();
	~Commands();

	void		execute(std::list<std::string> &operands);
	void		pop( void );
	void		dump( void );
	void		print( void );
	void		push( std::string line );
	void		assert( std::string line );
	void		add( void );
	void		sub( void );
	void		mul( void );
	void		div( void );
	void		mod( void );
	void		max( void );


	eOperandType        StringToType(std::string type);

	class EmptyStack : public std::exception {public : virtual const char *what() const throw();};
	class OperationWithZero  : public std::exception {public : virtual const char *what() const throw();};
	class Not8Bit : public std::exception {public : virtual const char *what() const throw();};
	class AssertProblem : public std::exception {public : virtual const char *what() const throw();};
private:
	std::list<IOperand const *> _stack;
	Operands					_operands;
	int							_counter;
};

#endif
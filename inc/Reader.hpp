#ifndef READER_HPP
# define READER_HPP

# include "Parser.hpp"
# include "Commands.hpp"

using std::string;
using std::cout;
using std::list;

class Reader
{

public:
	Reader(){};
	~Reader(){};
	Reader(Reader const &copy);

	void			readFromInput();
	void			readFromFile(string file);
	void			start_program();
	list<string>	getOperands();

	class FileNotFound : public std::exception { virtual const char* what() const throw();};
	class FileEmpty : public std::exception { virtual const char* what() const throw();};
	class IncorrectInput : public std::exception { virtual const char* what() const throw();};

private:
	list<string>		_operands;
	Parser				_parser;
	Commands			_commands;
};

#endif
#include "Reader.hpp"

Reader::Reader(Reader const &copy)
{
	this->_operands = copy._operands;
}

/////////////////////////////////////
///////////// Main functions ////////
/////////////////////////////////////


void    Reader::readFromInput()
{
	for (string line; std::getline(std::cin, line);)
	{
		if (line == "help")
		{
			std::cout << MAG "\tHi there!\n";
			std::cout << "This Abstract is created by aspizhav\n\n" FINISH;
			std::cout << "|-----------------\x1b[31;01m MENU \x1b[0m----------------|\n";
			std::cout << "| \tU can Use this instructions \t|\n";
			std::cout << "| \t\t \033[1;32m ADD\033[m \t\t\t|\n";	
			std::cout << "| \t\t \033[1;32m ASSERT\033[m \t\t|\n";
			std::cout << "| \t\t \033[1;32m DIV\033[m \t\t\t|\n";
			std::cout << "| \t\t \033[1;32m DUMP\033[m \t\t\t|\n";
			std::cout << "| \t\t \033[1;32m MOD\033[m \t\t\t|\n";
			std::cout << "| \t\t \033[1;32m MUL\033[m \t\t\t|\n";
			std::cout << "| \t\t \033[1;32m POOP\033[m \t\t\t|\n";
			std::cout << "| \t\t \033[1;32m PRINT\033[m \t\t|\n";
			std::cout << "| \t\t \033[1;32m PUSH (type)(value)\033[m \t|\n";
			std::cout << "| \t\t \033[1;32m SUB\033[m \t\t\t|\n";
			std::cout << "|---------------------------------------|\n\n\n";
			std::cout << GREEN << "Start! Good Luck!\n" FINISH;
		}
		this->_operands.push_back(line);
		if (line == ";;")
			break ;
		if (std::cin.eof())
			throw Reader::IncorrectInput();
	}
}

void    Reader::readFromFile(string file)
{
	std::ifstream fd;

	fd.open(file);
	if (!fd)
		throw Reader::FileNotFound();
	else if (fd.peek() == EOF)
		throw Reader::FileEmpty();
	else
	{
		for (string line; std::getline(fd, line);)
			this->_operands.push_back(line);
		fd.close();		
	}
}

void			Reader::start_program()
{
	this->_parser.parse(this->_operands);
	this->_commands.execute(this->_operands);
}

list<string>	Reader::getOperands()
{
	return (this->_operands);
}
/////////////////////////////////////
/////////////// Exceptions //////////
/////////////////////////////////////

const char *Reader::FileEmpty::what() const throw()
{
	return (RED "Error - File is empty!\n");
}

const char *Reader::FileNotFound::what() const throw()
{
	return (RED "Error - File not found!\n");
}

const char *Reader::IncorrectInput::what() const throw()
{
	return (RED "Error - Don't use EOF!\n");
}
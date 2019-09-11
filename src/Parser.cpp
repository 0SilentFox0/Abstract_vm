#include "Parser.hpp"
# include <cctype>
# include <sstream>

Parser::Parser()
{
	this->_counter = 0;
	this->_functions.push_back("pop");
	this->_functions.push_back("push");
	this->_functions.push_back("assert");
	this->_functions.push_back("add");
	this->_functions.push_back("sub");
	this->_functions.push_back("mul");
	this->_functions.push_back("div");
	this->_functions.push_back("mod");
	this->_functions.push_back("print");
	this->_functions.push_back("exit");
	this->_functions.push_back("dump");
	return ;
}

void		Parser::checkContent(std::string line)
{
	if (line.find('(') != std::string::npos)
	{
		std::string type = line.substr(line.find(' ') + 1, 5);
		if (type != "int8(" && type != "int16" && type != "int32" && type != "float" && type != "doubl")
			this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> Type Error!");
		int len = line.find(')') - line.find('(');
		if (len == 1)
			this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> Add more parameters!");
		std::string content = line.substr(line.find('(') + 1, len - 1);
		std::regex	regex1("^-?\\d+$");
		std::regex	regex2("^-?[0-9]\\d*(\\.\\d+)?$");
		if (type == "doubl" || type == "float")
		{
			for (std::string::iterator i = content.begin(); i != content.end(); ++i)
			{
				if (!std::regex_match(content, regex2))
					this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> Unexpected character!");
			}
		}
		else
		{
			for (std::string::iterator i = content.begin(); i != content.end(); ++i)
			{
				if (!std::regex_match(content, regex1))
					this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> Unexpected character for int type!");
			}
		}
		if ((std::count(line.begin(), line.end(), '(')) > 1 || (std::count(line.begin(), line.end(), ')')) > 1)
			this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> To many parameters!");
		if ((std::count(line.begin(), line.end(), '(')) < 1 || (std::count(line.begin(), line.end(), ')')) < 1)
			this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> Add more parameters!");
	}
}

void 	Parser::trim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void    Parser::parse(std::list<std::string> &operands)
{
	for (std::list<std::string>::iterator i = operands.begin(); i != operands.end(); ++i)
	{
		trim(*i);
		this->_counter++;

		std::string line = *i;
		if (line != "")
		{
			if (line[0] != ';')
			{
				if (!(std::find(this->_functions.begin(), this->_functions.end(), line.substr(0, line.find(" "))) != this->_functions.end()))
					this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + " No such commands!");
				else if (line.substr(0, line.find(" ")) == "push")
					checkContent(line);
			}
		}
	}
	std::list<std::string>::iterator i;
	for (i = operands.begin(); i != operands.end(); ++i){}
	i--;
	if (*i == ";;")
	{
		i--;
			if (*i != "exit")
				this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> No exit command!");
	}
	else
	{
		if (*i != "exit")
			this->_errors.push_back(RED "Parser Error on line -> " + std::to_string(this->_counter) + "-> No exit command!");
	}
	if (!this->_errors.empty())
		throw Error(this->_errors);
}


////////////////////////////////////////
//////////// Exceptions ///////////////
//////////////////////////////////////


Parser::Error::Error(std::list<std::string> errList) {
    for(std::list<std::string>::iterator i = errList.begin(); i != errList.end(); ++i) {
        _exceptions += (*i + '\n');
    }
}

Parser::Error::~Error() throw(){ return ; }

const char *Parser::Error::what() const throw() {
    return (this->_exceptions.c_str());
}

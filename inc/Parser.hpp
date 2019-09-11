#ifndef PARSER_HPP
# define PARSER_HPP
# include <string>
# include <exception>
# include <list>
# include <iostream>
# include <fstream>
# include <cctype>
# include <algorithm>
# include <regex>
#define RED "\033[31m"
#define MAG "\033[35m"

class Parser
{

public:
	Parser();
	~Parser(){};

	void	trim(std::string &str);
	void	parse(std::list<std::string> &operands);
	void	checkContent(std::string line);

	class Error : public std::exception {
        public:
            Error(std::list<std::string> errList);
            ~Error() _NOEXCEPT;
        private:
            virtual const char *what() const throw();
            std::string _exceptions;
    };

private:
	std::list<std::string> _errors;
	std::list<std::string> _functions;
	int				_counter;
};

#endif
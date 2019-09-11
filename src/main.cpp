#include "Reader.hpp"
#include "Parser.hpp"

int main(int ac, char **av)
{
	Reader	abstract;

	try
	{
		if (ac == 1)
		{
			std::cout << GREEN "If u don't know what u can do -> write [help]\n" FINISH;
			abstract.readFromInput();
		}
		else if (ac >= 2)
			abstract.readFromFile(av[1]);
		else
			throw Reader::IncorrectInput();		

		try
		{
			abstract.start_program();
		}
		catch(const std::exception& e)
		{
			std::cout << RED "Shit happens( \n" << e.what() << '\n';
		}		
	}
	catch(const std::exception& e)
	{
		std::cout << RED "Abstarct-VM problems(((" << e.what() << '\n';
	}
}
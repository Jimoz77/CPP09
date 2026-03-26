#include "RPN.hpp"
#include <exception>
#include<iostream>

int main(int ac, char **av)
{
	try
	{	
		if(ac != 2)
			throw WrongArgNb();
		std::string arg = av[1];
		RPN token;

		for(size_t i = 0; i < arg.size(); i++)
		{
			if((arg[i] - '0' < 0 || arg[i] - '0' > 9) && (arg[i] != ' ' && arg[i] != '+' && arg[i] != '-' && arg[i] != '*' && arg[i] != '/'))
				throw InvalChar();
			if(arg[i] != ' ')
				token.process(arg[i]);
		}
		std::cout << token.getResult() << std::endl;
	}
	catch(const std::exception &e )
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}

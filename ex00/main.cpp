#include "BitcoinExchange.hpp"
#include <exception>
#include <iterator>

//!!!!ATTENTION regarder si corriger test3 avant de push !!!!


int main(int ac, char**av)
{
	if(ac == 2)
	{
		try
		{
			inputData data(av[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << "ERROR: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "Wrong input detected, you must use this programe like that: ./btc example.txt" << std::endl;
		return (1);
	}
}

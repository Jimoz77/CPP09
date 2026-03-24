#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<algorithm>
#include<exception>
class inputData
{
	private:

		std::map<std::string, float> btcdata;

	public:
		inputData(std::string input);
		inputData(const inputData &other);

		inputData &operator=(const inputData &other);

		const std::map<std::string, float> mapper(std::string file);
		~inputData();


	class WFormatIput : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Wrong format! Format should be:\nyyyy-mm-dd | nb\n"); // preciser quel data a fail 
			}
	};
	class WNbInput : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Bitcoin value is invalid! The value should be postiv and lower than ...\n"); // preciser quel data a fail et quel est la maxvalue
			}
	};
	class WInputFile : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Input file can't be found or is empty!\n");
			}
	};

};




#endif // !BITCOINEXCHANGE_HPP

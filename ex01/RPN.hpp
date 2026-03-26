#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <exception>



typedef int (*opfunc)(int,int);
typedef struct s_token
{
	char token;
	opfunc func;
} t_token;

class RPN
{
	private:
		std::stack<int> _nbStack;
		t_token _tokens[4];
	public:
		RPN();
		int getResult();
		bool process(char arg);
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);

		
		~RPN();
};

class zeroDiv : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return ("Error: Division by zero!");
	}
};

class MissingNB : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return("Error: some number is missing to compete an operation");
		}
};

class WrongArgNb : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return ("Error: Wrong number of argument, the programme should be used like that: ./RPN  '2 2 +'");
	}
};

class InvalChar : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return ("Error: Invalid character found in argument string!");
	}
};

class InvalOpNb : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return("Error: Not enough operators for an operation,\nresult can't be returned because there is more than one number left on the stack!");	
	}
};

int Sub(int a, int b);
int Div(int a, int b);
int Multi(int a, int b);
int Add(int a, int b);

#endif

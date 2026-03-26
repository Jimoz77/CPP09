#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <cstdlib>


RPN::RPN()
{
	_tokens[0].token = '+'; _tokens[0].func = &Add;
	_tokens[1].token = '-'; _tokens[1].func = &Sub;
	_tokens[2].token = '*'; _tokens[2].func = &Multi;
	_tokens[3].token = '/'; _tokens[3].func = &Div;
}

int RPN::getResult() {if(_nbStack.size() != 1) throw InvalOpNb(); return _nbStack.top();}
int Add(int a, int b) { return (a + b);}
int Sub(int a, int b) { return (a - b);}
int Multi(int a, int b) {return (a * b);}
int Div(int a, int b) {if(b == 0)  throw zeroDiv(); return (a / b);}
bool RPN::process(char arg)
{
	bool found = false;
	if(std::isdigit(arg))
	{
		_nbStack.push(static_cast<int>(arg - '0'));
		found = true;
	}
	else
	{
		if(_nbStack.size() < 2 )
			throw MissingNB();
		int b = _nbStack.top();
		_nbStack.pop();
		int a = _nbStack.top();
		_nbStack.pop();
		char op = arg;
		for(int i = 0; i < 4; i++)
		{
			if(_tokens[i].token == op)
			{
				int result = _tokens[i].func(a,b);
				_nbStack.push(result);
				found = true;
				break;
			}
		}
	}	
	return found;
}
RPN::RPN(const RPN &other) : _nbStack(other._nbStack)
{
        for(int i=0; i<4; i++)
			this->_tokens[i] = other._tokens[i];

}
RPN& RPN::operator=(const RPN &other) 
{ 
    if (this != &other)
	{
        this->_nbStack = other._nbStack;
        for(int i=0; i<4; i++)
			this->_tokens[i] = other._tokens[i];
    }
    return *this; 
}
RPN::~RPN()
{

}


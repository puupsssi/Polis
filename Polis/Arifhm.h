#pragma once
#include "Poliz.h"

class Arifhm
{
private:
	std::string str;
	Poliz myPolis;
	Stack<double> myStack;

public:
	Arifhm(std::string str = "")
	{
		this->str = str;
		myPolis = Poliz(str);
		myStack = Stack<double>(20);
	}

	~Arifhm() {};

	Arifhm(const Arifhm& other)
	{
		str = other.str;
		myPolis = other.myPolis;
		myStack = other.myStack;
	}

	Arifhm& operator=(Arifhm other)
	{
		str = other.str;
		myPolis = other.myPolis;
		myStack = other.myStack;
		return *this;
	}

	double calculate()
	{
		double left;
		double right;
		double value;

		for (int i = 0; i < myPolis.getCount(); i++)
		{
			value = myPolis.getvariables()[myPolis[i]];
			if (value > -1) myStack.pushback(value);
			else
			{
				right = myStack.pop();
				left = myStack.pop();
				if (myPolis[i] == "+") myStack.pushback(left + right);

				if (myPolis[i] == "-") myStack.pushback(left - right);

				if (myPolis[i] == "*") myStack.pushback(left * right);

				if (myPolis[i] == "/") myStack.pushback(left / right);

				if (myPolis[i] == "^") myStack.pushback(pow(left, right));
			}
		}
		return myStack.pop();
	}

	void setVar(std::string key, double value)
	{
		myPolis.setVar(key, value);
	}

	Tabl getTablevarials()
	{
		return myPolis.getvariables();
	}

	Poliz GetPolis()
	{
		return myPolis;
	}
};

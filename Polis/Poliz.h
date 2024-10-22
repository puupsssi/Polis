#pragma once
#include <string>
#include "Table.h"
#include "Stack.h"


class Poliz
{
private:
	void StringToWond(std::string str, int& k, std::string* w)
	{
		std::string zn = "+-*/^()";
		k = 0;
		str += " ";
		for (int i = 0; i < str.length(); i++)
		{
			int l = zn.find(str[i]);
			if (l >= 0 && l < zn.length())
			{
				if (w[k].length() > 0) k++;

				w[k] = str[i];
				w[++k] = "";
			}
			else
			{
				if (str[i] == ' ')
				{
					if (w[k].length() > 0) w[++k] = "";
				}
				else w[k] = w[k] + str[i];
			}
		}
	}

	std::string* lex;
	int count, countlex, size, sizelex;
	std::string* memory;
	Stack<record> myStack;
	Tabl priorityTable;
	Tabl variables;

	void madePriorityTable() {
		priorityTable = Tabl(20);
		priorityTable.emplace("+", 0.0);
		priorityTable.emplace("-", 0.0);
		priorityTable.emplace("*", 1.0);
		priorityTable.emplace("/", 1.0);
		priorityTable.emplace("^", 2.0);
	}

	void workLeft() {
		myStack.pushback(record("(", -1.0));
	}

	void workRight() {
		while (!myStack.isEmpty() && myStack.top().key != "(") memory[count++] = myStack.pop().key;

		if (myStack.top().key == "(") myStack.pop();
	}

	void workOperand(std::string str)
	{
		memory[count++] = str;
		if (isdigit(str[0])) variables.emplace(str, std::stod(str));

		else variables.emplace(str, 0.0);

	}

	void workOperator(std::string str, int p)
	{
		while (!myStack.isEmpty() && myStack.top().value >= p) memory[count++] = myStack.pop().key;

		myStack.pushback(record(str, p));
	}

	void workEnd()
	{
		while (!myStack.isEmpty()) memory[count++] = myStack.pop().key;
	}

	void madePolis()
	{
		count = 0;
		for (int i = 0; i < countlex; i++)
		{
			if (lex[i] == "(") workLeft();
			else
			{
				if (lex[i] == ")") workRight();
				else
				{
					int p = priorityTable[lex[i]];
					if (p > -1) workOperator(lex[i], p);

					else workOperand(lex[i]);
				}
			}
		}
		workEnd();
	}

public:
	Poliz(std::string str = "")
	{
		size = str.length() + 1;
		variables = Tabl(size);
		memory = new std::string[size];
		count = 0;
		sizelex = size + 1;
		lex = new std::string[sizelex];
		countlex = 0;
		StringToWond(str, countlex, lex);
		madePriorityTable();
		myStack = Stack<record>(20);
		madePolis();
	}

	~Poliz()
	{
		delete[] memory;
	}

	Poliz(const Poliz& other)
	{
		size = other.size;
		count = other.count;
		memory = new std::string[size];
		for (int i = 0; i < size; i++) {
			memory[i] = other.memory[i];
		}
		priorityTable = other.priorityTable;
		myStack = other.myStack;
		variables = other.variables;
	}

	Poliz& operator =(const Poliz& other)
	{
		delete[] memory;
		size = other.size;
		count = other.count;
		memory = new std::string[size];
		for (int i = 0; i < size; i++) {
			memory[i] = other.memory[i];
		}
		priorityTable = other.priorityTable;
		myStack = other.myStack;
		variables = other.variables;

		return *this;
	}

	int getCount()
	{
		return count;
	}

	std::string operator[](int n)
	{
		if (n >= 0 && n < count) return memory[n];

		return "?";
	}

	std::string getStringPolis()
	{
		std::string str = memory[0];

		for (int i = 1; i < count; i++) str += " " + memory[i];

		return str;
	}

	Tabl getvariables()
	{
		return variables;
	}

	void setVar(std::string key, double value)
	{
		variables.emplace(key, value);
	}
};
#pragma once
#include <string>
#include <iostream>

using namespace std;
struct record
{
	string key;
	double value;
	record* next;

	record(string key = "", double value = 0)
	{
		this->key = key;
		this->value = value;
		next = nullptr;
	}
};

class Tabl
{
private:
	int maxSize;

	int hash(const string& key)
	{
		int hash = 1709;
		for (char c : key) hash = ((hash << 5) + hash) + c;

		return abs(hash);
	}

	int getIndex(int hash)
	{
		return hash % maxSize;
	}

	record** memory;

public:
	Tabl(int size = 10)
	{
		maxSize = size;
		memory = new record * [size]();
	}

	~Tabl()
	{
		for (int i = 0; i < maxSize; i++)
		{
			while (memory[i] != nullptr)
			{
				record* temp = memory[i]->next;
				delete memory[i];
				memory[i] = temp;
			}
		}

		delete[] memory;
	}

	Tabl(const Tabl& other)
	{
		maxSize = other.maxSize;
		memory = new record * [maxSize]();

		for (int i = 0; i < maxSize; i++)
		{
			if (other.memory[i] == nullptr) continue;
			memory[i] = new record(other.memory[i]->key, other.memory[i]->value);

			record* prev = other.memory[i];
			record* current = prev->next;
			record* myCurrent = memory[i];

			while (current != nullptr)
			{
				myCurrent->next = new record(current->key, current->value);
				myCurrent = myCurrent->next;
				prev = current;
				current = current->next;
			}
		}
	}

	Tabl& operator= (const Tabl& other)
	{
		for (int i = 0; i < maxSize; i++)
		{
			while (memory[i] != nullptr)
			{
				record* temp = memory[i]->next;
				delete memory[i];
				memory[i] = temp;
			}
		}

		delete[] memory;

		maxSize = other.maxSize;
		memory = new record * [maxSize]();

		for (int i = 0; i < maxSize; i++)
		{
			if (other.memory[i] == nullptr) continue;
			memory[i] = new record(other.memory[i]->key, other.memory[i]->value);

			record* prev = other.memory[i];
			record* current = prev->next;
			record* myCurrent = memory[i];

			while (current != nullptr)
			{
				myCurrent->next = new record(current->key, current->value);
				myCurrent = myCurrent->next;
				prev = current;
				current = current->next;
			}
		}

		return *this;
	}

	double operator[] (string key)
	{
		int index = getIndex(hash(key));
		if (memory[index] == nullptr) return -1;

		record* current = memory[index];
		while (current->next != nullptr && current->key != key)
		{
			current = current->next;
		}

		if (current->key == key)
		{
			return current->value;
		}

		return -1;
	}

	string operator[] (int number)
	{
		if (number >= getCount()) return "?";

		int it = 0;
		string result = "?";

		for (int i = 0; i < maxSize; i++)
		{
			record* current = memory[i];
			while (current != nullptr)
			{

				if (it == number) return current->key;
				it++;
				current = current->next;
			}
		}

		return result;
	}

	bool emplace(string key, double value)
	{
		int index = getIndex(hash(key));
		if (memory[index] == nullptr)
		{
			memory[index] = new record(key, value);
			return true;
		}

		record* current = memory[index];
		while (current->next != nullptr && current->key != key)
		{
			current = current->next;
		}

		if (current->key == key)
		{
			current->value = value;
			return false;
		}

		current->next = new record(key, value);
		return true;
	}

	bool erase(string key)
	{
		int index = getIndex(hash(key));

		if (memory[index] == nullptr) return false;
		if (memory[index]->key == key)
		{
			delete memory[index];
			memory[index] = nullptr;
			return true;
		}

		record* current = memory[index];

		while (current->next != nullptr && current->next->key != key)
		{
			current = current->next;
		}

		if (current->next == nullptr) return false;

		delete current->next;
		current->next = nullptr;
		return true;
	}

	bool empty()
	{
		for (int i = 0; i < maxSize; i++) if (memory[i] != nullptr) return false;

		return true;
	}

	void print()
	{
		for (int i = 0; i < maxSize; i++)
		{
			cout << i << endl;

			record* current = memory[i];
			while (current != nullptr)
			{
				cout << current->key << " " << current->value << endl;
				current = current->next;
			}
		}
	}

	int getCount()
	{
		int result = 0;

		for (int i = 0; i < maxSize; i++)
		{
			record* current = memory[i];
			while (current != nullptr)
			{
				result++;
				current = current->next;
			}
		}

		return result;
	}
};
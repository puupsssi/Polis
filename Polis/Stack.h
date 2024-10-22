#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Stack
{
private:
	T* Mem;//стек
	int size;//размер стека
	int count; //показывает на первый пустой элемент
public:
	Stack(int _size = 20)
	{
		size = _size;
		count = 0;
		Mem = new T[size];
		for (int i = 0; i < size; i++)
		{
			Mem[i] = T();
		}
	}
	~Stack()
	{
		delete[]Mem;
	}
	Stack(const Stack& tmp) //конструктор копирования
	{
		size = tmp.size;
		count = tmp.count;
		Mem = new T[size];
		for (int i = 0; i < size; i++)
		{
			Mem[i] = tmp.Mem[i];
		}
	}
	Stack& operator=(Stack tmp) //оператор присваивания
	{
		if (size != tmp.size)
		{
			if (size != 0)
			{
				delete[]Mem;
			}
			size = tmp.size;
			Mem = new T[size];
		}
		count = tmp.count;
		for (int i = 0; i < size; i++)
		{
			Mem[i] = tmp.Mem[i];
		}
		return *this;
	}
	void pushback(T val) //положить в стек
	{
		if (count != size)
		{
			Mem[count++] = val;
		}
	}
	T pop()//взять из стека
	{
		if (count > 0)
		{
			return Mem[--count];
		}
		T res = T(0);
		return res;
	}
	T top()//просмотр верхнего элемента в стеке
	{
		if (count > 0)
		{
			return Mem[count - 1];
		}
		T res = T(0);
		return res;
	}
	int isEmpty()//проверка на пустоту
	{
		if (count == 0)
		{
			return 1;//пустой стек
		}
		else
		{
			return 0;//непустой стек
		}
	}
	int isFull()//проверка на полноту
	{
		if (size == count)
		{
			return 1;//пустой стек
		}
		else
		{
			return 0;//непустой стек
		}
	}
};




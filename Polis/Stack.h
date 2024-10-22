#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Stack
{
private:
	T* Mem;//����
	int size;//������ �����
	int count; //���������� �� ������ ������ �������
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
	Stack(const Stack& tmp) //����������� �����������
	{
		size = tmp.size;
		count = tmp.count;
		Mem = new T[size];
		for (int i = 0; i < size; i++)
		{
			Mem[i] = tmp.Mem[i];
		}
	}
	Stack& operator=(Stack tmp) //�������� ������������
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
	void pushback(T val) //�������� � ����
	{
		if (count != size)
		{
			Mem[count++] = val;
		}
	}
	T pop()//����� �� �����
	{
		if (count > 0)
		{
			return Mem[--count];
		}
		T res = T(0);
		return res;
	}
	T top()//�������� �������� �������� � �����
	{
		if (count > 0)
		{
			return Mem[count - 1];
		}
		T res = T(0);
		return res;
	}
	int isEmpty()//�������� �� �������
	{
		if (count == 0)
		{
			return 1;//������ ����
		}
		else
		{
			return 0;//�������� ����
		}
	}
	int isFull()//�������� �� �������
	{
		if (size == count)
		{
			return 1;//������ ����
		}
		else
		{
			return 0;//�������� ����
		}
	}
};




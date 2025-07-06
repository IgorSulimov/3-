#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;


struct Pair
{
	int number;
	int value;
};

class Iterator;

class Vector
{
private:
	Pair* Arr_Vect;
	int current_size;
	int size;
public:
	// Constructor
	Vector(int* arr = nullptr, int size_arr = 0)
	{
		Arr_Vect = new Pair[size_arr];
		current_size = 0;
		size = size_arr;
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i] != 0)
			{
				Arr_Vect[current_size].number = i;
				Arr_Vect[current_size].value = arr[i];
				current_size++;
			}
		}
	}
	Vector(const Vector& other_)
	{
		if (other_.size == 0)
		{
			Arr_Vect = nullptr;
			size = 0;
			current_size = 0;
		}
		else
		{
			Arr_Vect = new Pair[other_.current_size];
			size = other_.size;
			current_size = 0;
			while (current_size < other_.current_size)
			{
				Arr_Vect[current_size] = other_.Arr_Vect[current_size];
				current_size++;
			}
		}
	}
	// Destructor
	~Vector()
	{
		delete[] Arr_Vect;
	}

	void Set_El_Arr(int index_Arr, int val)
	{
		int ind = -1;
		if (index_Arr > size - 1 || size < 0)
		{
			return;
		}
		// Если val != 0
		if (val != 0)
		{
			for (int i = 0; i < current_size; i++)
			{
				if (Arr_Vect[i].number == index_Arr)
				{
					Arr_Vect[i].value = val;
					return;
				}
			}
		}
		// Если val = 0
		else
		{
			for (int i = 0; i < current_size; i++)
			{
				if (Arr_Vect[i].number == index_Arr)
				{
					ind = i;
					i = current_size;
				}
			}
			if (ind != -1)
			{
				Vector tmp;
				tmp.size = size;
				tmp.current_size = current_size - 1;
				tmp.Arr_Vect = new Pair[size+1];
				for (int i = 0; i < current_size; i++)
				{
					if (i == ind)
					{

					}
					else
					{
						tmp.Arr_Vect[i] = Arr_Vect[i];
					}
				}
				delete[] Arr_Vect;
				current_size--;
				Arr_Vect = new Pair[size];
				for (int i = 0; i < current_size; i++)
				{
					Arr_Vect[i] = tmp.Arr_Vect[i];
				}
				return;
			}
		}
		// Если size < current_size Увеличиваем память в Arr_Vect
		current_size++;
		if (size > current_size)
		{
			Arr_Vect[current_size].number = index_Arr;
			Arr_Vect[current_size].value = val;
		}
		else
		{
			Vector tmp;
			tmp.size = current_size;
			tmp.current_size = current_size;
			tmp.Arr_Vect = new Pair[current_size];
			for (int i = 0; i < tmp.size; i++)
			{
				tmp.Arr_Vect[i] = Arr_Vect[i];
			}
			delete[] Arr_Vect;
			size = current_size;
			Arr_Vect = new Pair[size];
			for (int i = 0; i < size; i++)
			{
				Arr_Vect[i] = tmp.Arr_Vect[i];
			}
			delete[] tmp.Arr_Vect;
		}
	}
	// доступ к элементам
	int Get_number_Arr(int index_Arr)
	{
		return Arr_Vect[index_Arr].number;
	}
	int Get_value_Arr(int index_Arr)
	{
		return Arr_Vect[index_Arr].value;
	}
	int Get_size_Arr()
	{
		return size;
	}
	void Print_Vector()
	{
		for (int i = 0; i < current_size; i++)
		{
			printf("%d|%d\n", Arr_Vect[i].number, Arr_Vect[i].value);
		}
	}
	// Оператор присваивания
	Vector& operator =(const Vector& other_);
	// Поэлементные арифметические действия + - * / %
	Vector operator +(const Vector& other_)const;
	Vector operator -(const Vector& other_)const;
	Vector operator *(const Vector& other_)const;
	Vector operator /(const Vector& other_)const;
	Vector operator %(const Vector& other_)const;
	// скалярное произведение & 
	int operator &(const Vector& other_)const;
	// ввод вывод в виде - элементы, через запятую
	friend ostream& operator <<(ostream& stream, const Vector& vec);
	friend istream& operator >>(istream& in, Vector& vec);
	// сравнения
	bool operator ==(const Vector& other_);
	bool operator !=(const Vector& other_);
	bool operator !();
	// конкатенация
	Vector Concatenation(const Vector& other_) const;
	// выделение подвектора
	Vector Subvector_Selection(int from, int to);
	// сдвиги
	Vector& Shift_left(int shift);
	Vector& Shift_right(int shift);
	// Бинарный поиск
	int Binary_Search(int element);

	//Итераторы 
	Iterator begin() const;
	Iterator end() const;
};

class Iterator
{
	Pair* ptr;
	int index;

public:
	Iterator(Pair* ptr_, int index_)
	{
		ptr = ptr_;
		index = index_;
	}
	Pair& operator*() const
	{
		return *ptr;
	}
	Pair* operator->() const
	{
		return ptr;
	}
	bool operator==(const Iterator& it) const
	{
		return (index == it.index && ptr == it.ptr);
	}
	bool operator!=(const Iterator& it) const
	{
		return (index != it.index && ptr != it.ptr);
	}
	Iterator& operator++()
	{
		index++;
		return *this;
	}
	Iterator operator++(int x)
	{
		index += x;
		return *this;
	}
	friend class Vector;

};

ostream& operator <<(ostream& stream, const Vector& vec);
istream& operator >>(istream& in, Vector& vec);
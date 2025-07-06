#include "Vector.hpp"

Vector& Vector::operator=(const Vector& other_)
{
	if (other_.size == 0)
	{
		delete[] Arr_Vect;
		size = 0;
		current_size = 0;
		Arr_Vect = nullptr;
		return *this;
	}
	if (this == &other_)
		return *this;

	delete[] Arr_Vect;
	Arr_Vect = new Pair[other_.current_size];
	size = other_.size;
	current_size = 0;
	while (current_size < other_.current_size)
	{
		Arr_Vect[current_size].number = other_.Arr_Vect[current_size].number;
		Arr_Vect[current_size].value = other_.Arr_Vect[current_size].value;
		current_size++;
	}
	return *this;
}

Vector Vector::operator+(const Vector& other_) const
{
	if (size != other_.size)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector tmp;
	delete[] tmp.Arr_Vect;
	int sum_cur = current_size + other_.current_size;
	tmp.Arr_Vect = new Pair[sum_cur+1];
	tmp.size = size;
	tmp.current_size = 0;
	int count_this = 0, count_other = 0, count_tmp = 0;
	while (count_this < current_size && count_other < other_.current_size)
	{
		if (Arr_Vect[count_this].number == other_.Arr_Vect[count_other].number)
		{
			if (Arr_Vect[count_this].value != -other_.Arr_Vect[count_other].value)
			{
				tmp.Arr_Vect[count_tmp].number = Arr_Vect[count_this].number;
				tmp.Arr_Vect[count_tmp].value = Arr_Vect[count_this].value + other_.Arr_Vect[count_other].value;
				tmp.current_size++;
			}
			count_this++;
			count_other++;
			count_tmp++;
		}
		if (Arr_Vect[count_this].number > other_.Arr_Vect[count_other].number && count_other < other_.current_size)
		{

			tmp.Arr_Vect[count_tmp] = other_.Arr_Vect[count_other];
			count_other++;
			count_tmp++;
			tmp.current_size++;

		}
		if (Arr_Vect[count_this].number < other_.Arr_Vect[count_other].number && count_this < current_size)
		{
			tmp.Arr_Vect[count_tmp] = Arr_Vect[count_this];
			count_this++;
			count_tmp++;
			tmp.current_size++;

		}
	}
	Vector res;
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[tmp.current_size];
	res.size = size;
	res.current_size = tmp.current_size;
	for (int i = 0; i < res.current_size; i++)
	{
		res.Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return res;
}

Vector Vector::operator -(const Vector& other_) const
{
	if (size != other_.size)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector tmp;
	delete[] tmp.Arr_Vect;
	int sum_cur = current_size + other_.current_size;
	tmp.Arr_Vect = new Pair[sum_cur+1];
	tmp.size = size;
	tmp.current_size = 0;
	int count_this = 0, count_other = 0, count_tmp = 0;
	while (count_this < current_size && count_other < other_.current_size)
	{
		if (Arr_Vect[count_this].number == other_.Arr_Vect[count_other].number)
		{
			if (Arr_Vect[count_this].value != other_.Arr_Vect[count_other].value)
			{
				tmp.Arr_Vect[count_tmp].number = Arr_Vect[count_this].number;
				tmp.Arr_Vect[count_tmp].value = Arr_Vect[count_this].value - other_.Arr_Vect[count_other].value;
				tmp.current_size++;
			}
			count_this++;
			count_other++;
			count_tmp++;
		}
		if (Arr_Vect[count_this].number > other_.Arr_Vect[count_other].number && count_other < other_.current_size)
		{
			tmp.Arr_Vect[count_tmp].number = other_.Arr_Vect[count_other].number;
			tmp.Arr_Vect[count_tmp].value = -other_.Arr_Vect[count_other].value;
			count_other++;
			count_tmp++;
			tmp.current_size++;

		}
		if (Arr_Vect[count_this].number < other_.Arr_Vect[count_other].number && count_this < current_size)
		{
			tmp.Arr_Vect[count_tmp] = Arr_Vect[count_this];
			count_this++;
			count_tmp++;
			tmp.current_size++;

		}
	}
	while (count_this < current_size)
	{
		tmp.Arr_Vect[count_tmp] = Arr_Vect[count_this];
		count_this++;
		count_tmp++;
		tmp.current_size++;
	}
	while (count_other < other_.current_size)
	{
		tmp.Arr_Vect[count_tmp].number = other_.Arr_Vect[count_other].number;
		tmp.Arr_Vect[count_tmp].value = -other_.Arr_Vect[count_other].value;
		count_other++;
		count_tmp++;
		tmp.current_size++;
	}
	Vector res;
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[tmp.current_size];
	res.size = size;
	res.current_size = tmp.current_size;
	for (int i = 0; i < res.current_size; i++)
	{
		res.Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return res;
}

Vector Vector::operator *(const Vector& other_) const
{
	if (size != other_.size)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector tmp;
	delete[] tmp.Arr_Vect;
	int sum_cur = current_size + other_.current_size;
	tmp.Arr_Vect = new Pair[sum_cur+1];
	tmp.size = size;
	tmp.current_size = 0;
	int count_this = 0, count_other = 0, count_tmp = 0;
	while (count_this < current_size && count_other < other_.current_size)
	{
		if (Arr_Vect[count_this].number == other_.Arr_Vect[count_other].number)
		{
			tmp.Arr_Vect[count_tmp].number = Arr_Vect[count_this].number;
			tmp.Arr_Vect[count_tmp].value = Arr_Vect[count_this].value * other_.Arr_Vect[count_other].value;
			count_this++;
			count_other++;
			count_tmp++;
			tmp.current_size++;

		}
		if (Arr_Vect[count_this].number > other_.Arr_Vect[count_other].number && count_other < other_.current_size)
		{
			count_other++;

		}
		if (Arr_Vect[count_this].number < other_.Arr_Vect[count_other].number && count_this < current_size)
		{
			count_this++;

		}
	}
	Vector res;
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[tmp.current_size];
	res.size = size;
	res.current_size = tmp.current_size;
	for (int i = 0; i < res.current_size; i++)
	{
		res.Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return res;
}
Vector Vector::operator/(const Vector& other_) const
{
	if (size != other_.size)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector tmp;
	delete[] tmp.Arr_Vect;
	int sum_cur = current_size + other_.current_size;
	tmp.Arr_Vect = new Pair[sum_cur+1];
	tmp.size = size;
	tmp.current_size = 0;
	int count_this = 0, count_other = 0, count_tmp = 0;
	while (count_this < current_size && count_other < other_.current_size)
	{
		if (Arr_Vect[count_this].number == other_.Arr_Vect[count_other].number)
		{
			if (Arr_Vect[count_this].value >= other_.Arr_Vect[count_other].value)
			{
				tmp.Arr_Vect[count_tmp].number = Arr_Vect[count_this].number;
				tmp.Arr_Vect[count_tmp].value = Arr_Vect[count_this].value / other_.Arr_Vect[count_other].value;
				tmp.current_size++;
			}
			count_this++;
			count_other++;
			count_tmp++;
		}
		if (Arr_Vect[count_this].number > other_.Arr_Vect[count_other].number && count_other < other_.current_size)
		{
			count_other++;
		}
		if (Arr_Vect[count_this].number < other_.Arr_Vect[count_other].number && count_this < current_size)
		{
			exit(-1);

		}
	}
	while (count_this < current_size)
	{
		exit(-1);
	}
	Vector res;
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[tmp.current_size];
	res.size = size;
	res.current_size = tmp.current_size;
	for (int i = 0; i < res.current_size; i++)
	{
		res.Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return res;
}
Vector Vector::operator%(const Vector& other_) const
{
	if (size != other_.size)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector tmp;
	delete[] tmp.Arr_Vect;
	int sum_cur = current_size + other_.current_size;
	tmp.Arr_Vect = new Pair[sum_cur+1];
	tmp.size = size;
	tmp.current_size = 0;
	int count_this = 0, count_other = 0, count_tmp = 0;
	while (count_this < current_size && count_other < other_.current_size)
	{
		if (Arr_Vect[count_this].number == other_.Arr_Vect[count_other].number)
		{
			if (Arr_Vect[count_this].value >= other_.Arr_Vect[count_other].value)
			{
				tmp.Arr_Vect[count_tmp].number = Arr_Vect[count_this].number;
				tmp.Arr_Vect[count_tmp].value = Arr_Vect[count_this].value / other_.Arr_Vect[count_other].value;
				tmp.current_size++;
			}
			count_this++;
			count_other++;
			count_tmp++;

		}
		if (Arr_Vect[count_this].number > other_.Arr_Vect[count_other].number && count_other < other_.current_size)
		{
			count_other++;
		}
		if (Arr_Vect[count_this].number < other_.Arr_Vect[count_other].number && count_this < current_size)
		{
			exit(-1);

		}
	}
	while (count_this < current_size)
	{
		exit(-1);
	}
	Vector res;
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[tmp.current_size];
	res.size = size;
	res.current_size = tmp.current_size;
	for (int i = 0; i < res.current_size; i++)
	{
		res.Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return res;
}

int Vector::operator&(const Vector& other_) const
{
	if (size == 0)
		return -1;

	if (size != other_.size)
		return -1;

	int res = 0, i = 0, j = 0;

	while (i < current_size || j < other_.current_size)
	{
		if (Arr_Vect[i].number == other_.Arr_Vect[j].number)
		{
			res += Arr_Vect[i].value * other_.Arr_Vect[j].value;
			i++;
			j++;
		}
		if (Arr_Vect[i].number > other_.Arr_Vect[j].number)
		{
			j++;
		}
		if (Arr_Vect[i].number < other_.Arr_Vect[j].number)
		{
			i++;
		}
	}
	return res;
}

bool Vector::operator==(const Vector& other_)
{
	if (current_size != other_.current_size || size != other_.size)
		return false;

	for (int i = 0; i < current_size; i++)
	{
		if (Arr_Vect[i].value != other_.Arr_Vect[i].value || Arr_Vect[i].number != other_.Arr_Vect[i].number)
			return false;
	}
	return true;
}

bool Vector::operator!=(const Vector& other_)
{
	if (current_size != other_.current_size || size != other_.size)
		return true;

	for (int i = 0; i < current_size; i++)
	{
		if (Arr_Vect[i].value == other_.Arr_Vect[i].value || Arr_Vect[i].number == other_.Arr_Vect[i].number)
			return false;
	}
	return true;
}

bool Vector::operator!()
{
	return(size == 0);
}

Vector Vector::Concatenation(const Vector& other_) const
{
	Vector res(nullptr, 0);
	if (other_.size == 0 && current_size != 0)
	{
		return *this;
	}
	if (size == 0 && other_.current_size != 0)
	{
		return other_;
	}
	if (size == 0 && other_.size == 0)
	{
		return res;
	}
	else
	{
		delete[] res.Arr_Vect;
		res.Arr_Vect = new Pair[current_size + other_.current_size];
		res.size = size + other_.size;
		for (res.current_size = 0; res.current_size < current_size; res.current_size++)
		{
			res.Arr_Vect[res.current_size].number = Arr_Vect[res.current_size].number;
			res.Arr_Vect[res.current_size].value = Arr_Vect[res.current_size].value;
		}
		int up_number = current_size;
		for (int i = 0; i < other_.current_size; i++)
		{
			res.Arr_Vect[res.current_size].number = other_.Arr_Vect[i].number + up_number;
			res.Arr_Vect[res.current_size].value = other_.Arr_Vect[i].value;
			res.current_size++;
		}
	}
	return res;
}

Vector& Vector::Shift_left(int shift)
{
	Vector tmp(nullptr, 0);
	if (size == 0)
	{
		return *this;
	}
	delete[] tmp.Arr_Vect;
	tmp.size = size;
	tmp.current_size = 0;
	tmp.Arr_Vect = new Pair[size+1];
	int to_index = current_size;
	for (int i = 0; i < current_size; i++)
	{
		if (Arr_Vect[i].number >= shift)
		{
			tmp.Arr_Vect[tmp.current_size].number = Arr_Vect[i].number - shift;
			tmp.Arr_Vect[tmp.current_size].value = Arr_Vect[i].value;
			tmp.current_size++;
		}
	}
	delete[] Arr_Vect;
	size = tmp.size;
	current_size = tmp.current_size;
	Arr_Vect = new Pair[current_size];
	for (int i = 0; i < tmp.current_size; i++)
	{
		Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return *this;
}
Vector& Vector::Shift_right(int shift)
{
	Vector tmp(nullptr, 0);
	if (size == 0)
	{
		return *this;
	}
	delete[] tmp.Arr_Vect;
	tmp.size = size;
	tmp.current_size = 0;
	tmp.Arr_Vect = new Pair[size+1];
	int to_index = current_size;
	for (int i = 0; i < current_size; i++)
	{
		if(Arr_Vect[i].number < current_size-shift)
		{
			tmp.Arr_Vect[tmp.current_size].number = Arr_Vect[i].number + shift;
			tmp.Arr_Vect[tmp.current_size].value = Arr_Vect[i].value;
			tmp.current_size++;
		}
	}
	delete[] Arr_Vect;
	size = tmp.size;
	current_size = tmp.current_size;
	Arr_Vect = new Pair[current_size];
	for (int i = 0; i < tmp.current_size; i++)
	{
		Arr_Vect[i] = tmp.Arr_Vect[i];
	}
	return *this;
}

Vector Vector::Subvector_Selection(int from, int to)
{
	if (size == 0 || from < 0 || from > to || to < 0)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	Vector res;
	res.size = 0;
	res.current_size = 0;
	int i = Binary_Search(from);
	int j = Binary_Search(to);
	res.size = j - i + 1;
	if (i == -1 || j == -1)
	{
		Vector tmp(nullptr, 0);
		return tmp;
	}
	delete[] res.Arr_Vect;
	res.Arr_Vect = new Pair[j - i + 1];
	while (i <= j)
	{
		res.Arr_Vect[res.current_size].number = Arr_Vect[i].number;
		res.Arr_Vect[res.current_size].value = Arr_Vect[i].value;
		i++;
		res.current_size++;
	}
	return res;
}

int Vector::Binary_Search(int element)
{
	int i = 0;
	int j = size - 1;
	int middle;
	if (Arr_Vect[i].value == element)
		return i;
	if (Arr_Vect[j].value == element)
		return j;
	while (i <= j)
	{
		middle = i + (j - i) / 2;
		if (Arr_Vect[middle].value > element)
		{
			j = middle - 1;
		}
		if (Arr_Vect[middle].value < element)
		{
			i = middle + 1;
		}
		if (Arr_Vect[middle].value == element)
			return middle;
	}
	return-1;
}

ostream& operator<<(ostream& stream, const Vector& vec)
{
	stream << "[";
	if (vec.current_size == 0)
	{

		for (int i = 0; i < vec.size - 1; i++)
		{
			stream << 0 << ",";
		}
		stream << 0 << "]" << endl;
	}
	else
	{
		int counter = 0;
		int k = vec.current_size - 1;
		for (int i = 0; i < k;)
		{
			if (counter == vec.Arr_Vect[i].number)
			{
				stream << vec.Arr_Vect[i].value << ",";
				counter++;
				i++;
			}
			else
			{
				counter++;
				stream << 0 << ",";
			}
		}
		while (counter < vec.Arr_Vect[k].number)
		{
			stream << 0 << ",";
			counter++;
		}
		if (vec.Arr_Vect[k].number < vec.size - 1)
		{
			stream << vec.Arr_Vect[k].value << ',';
			while (counter < vec.size - 2)
			{
				stream << 0 << ",";
				counter++;
			}
			stream << 0 << "]" << endl;
		}
		else
		{
			stream << vec.Arr_Vect[k].value << "]" << endl;
		}
	}
	return stream;
}

istream& operator>>(istream& in, Vector& vec)
{
	try
	{
		char ch;
		int ss = 100;
		vec.current_size = 0;
		vec.size = 0;

		delete[] vec.Arr_Vect;
		vec.Arr_Vect = new Pair[ss];
		in >> ch;
		if (ch != '[')
			throw ("В начале должна идти [\n");

		int value;
		in >> value;
		if (value != 0)
		{
			vec.Arr_Vect[vec.current_size].value = value;
			vec.Arr_Vect[vec.current_size].number = vec.size;
			vec.current_size++;
		}
		vec.size++;
		if (!in.good())
		{
			throw ("Неправильный ввод\n");
		}
		while (in.peek() == ',')
		{
			if (vec.size > ss)
			{
				Vector res;
				delete[] res.Arr_Vect;
				res.size = vec.size;
				res.current_size = vec.current_size;
				res.Arr_Vect = new Pair[vec.size + 1];
				for (int i = 0; i < res.current_size; i++)
				{
					res.Arr_Vect[i] = vec.Arr_Vect[i];
				}
				delete[] vec.Arr_Vect;
				vec.Arr_Vect = new Pair[ss * 2];
				for (int i = 0; i < vec.current_size; i++)
				{
					vec.Arr_Vect[i] = res.Arr_Vect[i];
				}
				ss *= 2;
			}
			in.ignore();
			in >> value;
			if (!in.good())
			{
				throw ("Неправильный ввод\n");
			}
			if (value != 0)
			{
				vec.Arr_Vect[vec.current_size].value = value;
				vec.Arr_Vect[vec.current_size].number = vec.size;
				vec.current_size++;
			}
			vec.size++;
		}
		if (in.peek() == ']')

			in.ignore();
		else
		{
			throw ("В конце должно стоять ]\n ");
		}
	}


	catch (string ex)
	{
		cout << ex <<endl;
	}

	return in;
}

Iterator Vector::begin() const
{
	return Iterator(Arr_Vect, 0);
}
Iterator Vector::end() const
{
	return Iterator(Arr_Vect, current_size);
}
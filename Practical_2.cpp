#include <iostream>

using namespace std;


class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor";
		ptr = new double[Dimension]; // выделяем память с помощью new
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		//заполнить массив ptr, заполнить поля
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		if (ptr != NULL)
		{
			delete[] ptr; // освобождаем свободную память 
			ptr = NULL;
		}
	}

	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }

	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		
	}

	//добавление в конец нового значения 
	void push(double value)
	{
		if (capacity > count)
		{
			ptr[count] = value;
			count += 1;
		}
		else
			return;
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count > 0)
			count -= 1;
	}

	double& operator[](int index)
	{
		if (index < 0)
			return ptr[count + index];
		if (count > index)
			return ptr[index];
	}

	MyArrayParent& operator=(const MyArrayParent& V)
	{
		count = V.count;

		ptr = new double[V.capacity];
		for (int i = 0; i < V.count; i++)
			ptr[i] = V.ptr[i];
		return *this; 
	}

 	MyArrayParent(const MyArrayParent& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		capacity = V.capacity;
		count = V.count;

		ptr = new double[V.capacity];
		for (int i = 0; i < V.count; i++)
			ptr[i] = V.ptr[i];
	}

	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

};

class MyArrayChild : public MyArrayParent
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	void RemoveAt(int index)
	{
		if (abs(index) < count)
		{
			if (index > 0)
			{
				for (int i = index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
				count -= 1;
			}
			if (index < 0)
			{
				for (int i = count + index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
			}
		}
	}

	int IndexOf(double value, bool bFindFromStart)
	{
		if (bFindFromStart == true) // линейный поиск
		{
			for (int i = 0; i < count; i++)
				if (ptr[i] == value)
					return i;
			return -1;
		}
	}

	//вставка элемента
	void InsertAt(double value, int index)
	{
		if (index > 0)
		{
			for (int i = count - 1; i >= index; i--)
			{
				ptr[i + 1] = ptr[i];
			}
			ptr[index] = value;
			count++;
		}
	}

	MyArrayChild Index_element(int element)
	{
		MyArrayChild t;
		cout << "\nIndex_element:\n";
		int j = 0;
		for (int i = 0; i < count; i++)
			if (ptr[i] == element)
			{
				t.push(i);
			}
		return t;
		
	}

	MyArrayChild SubSequence(int ind, int len)
	{
		MyArrayChild t;
		cout << "\nSubSequence:\n";
		int j = 0;
		for (int i = ind; i < ind + len && i < count; i++)
			t.push(ptr[i]);
		return t;
	}


	
};

class MySortedArray : public MyArrayChild
{
protected:
	int IndexOf_1(double value, bool bFindFromStart)// бинарный поиск
	{
		if (bFindFromStart == true)
		{
			int l = 0;
			int r = count;
			int mid;

			while (l <= r)
			{
				mid = (l + r) / 2;
				if (ptr[mid] == value)
					return mid;
				if (value < ptr[mid])
					r = mid - 1;
				if (value > ptr[mid])
					l = mid + 1;
			}
			return mid;
		}
	}

	int BinaryFind_1(double value, int left, int right) // бинарный поиск через рекурсию для вставки элемента
	{
		int middle = (left + right) / 2;

		double eps = 0.001;

		if (right == left + 1)
		{
			if (fabs(ptr[left] - value) < eps)
				return left;
			if (fabs(ptr[right] - value) < eps)
				return right;
			if (value < ptr[left])
				return left - 1;
			if (value > ptr[right])
				return right;
			return left;
		}

		// база рекурсии 
		if (fabs(ptr[middle] - value) < eps)
			return middle;

		if (ptr[middle] > value)
			return BinaryFind_1(value, left, middle);
		else
			return BinaryFind_1(value, middle, right);
	}

	/*void RemoveAt(int index)
	{
		if (abs(index) < count)
		{
			if (index > 0)
			{
				for (int i = index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
				count -= 1;
			}
			if (index < 0)
			{
				for (int i = count + index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
			}
		}
	}
	*/
public:
	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	/*virtual int IndexOf(double value, bool bFindFromStart)
	{
		if (bFindFromStart == true) // линейный поиск
		{
			for (int i = 0; i < count; i++)
				if (ptr[i] == value)
					return i;
			return -1;
		}
	}
	*/
	virtual void push(double x) // общая сложность О(n) = О(n) + O(log n) - вставка + бинарный поиск
	{

		if (count == 0)
		{
			MyArrayParent::push(x);
			return;

		}
		if (count == 1)
		{
			if (ptr[0] > x)
			{
				//InsertAt(x, 0);
				ptr[1] = ptr[0];
				ptr[0] = x;
				count++;
			}
			else
				MyArrayParent::push(x);
		}
		else
		{
			int index = BinaryFind_1(x, 0, count);
			if (index < 0)
			{
				InsertAt(ptr[0], 1);
				ptr[0] = x;

			}
			else
				InsertAt(x, index);
		}
	}

	virtual MySortedArray Index_element(int element)
	{
		cout << "\nIndex_element:\n";
		int r, r_1 = 101;
		int k = element;
		MySortedArray t;
		while (k != element + 2)
		{
			r = IndexOf(k, true);
			if (r - r_1 > 1)
				for (int i = r_1; i < r; i++)
				{
					t.push(i);
				}
			k++;
			r_1 = r;
		}
		return t;
	}
};

int main()
{
	//MyArrayParent arr;
	if (true)
	{
		
		MySortedArray arr;
		MyArrayChild t;
		for (int i = 0; i < 10; i++)
		{
			arr.push((i + 1) / 2);
		}
		//arr.push(5);
		//arr.IndexOf(1, true);
		t = arr.Index_element(4);
		t.print();
		arr.print();
		//cout << "\n" << arr.IndexOf(15, true);
		cout << "\n";

		MyArrayChild array;
		MyArrayChild kr;
		for (int i = 0; i < 10; i++)
		{
			array.push(i + 1);
		}
		t = array.Index_element(4);
		t.print();
		kr = array.SubSequence(5, 8);
		kr.print();
		array.print();
		
		MyArrayChild arr_z;
		MyArrayChild tr;
		for (int i = 10; i > 0; i--)
		{
			arr_z.push(i);
		}
		t = arr_z.Index_element(4);
		t.print();
		tr = arr_z.SubSequence(5, 2);
		tr.print();
		arr_z.print();
	}
	char c; cin >> c;
	return 0;

}

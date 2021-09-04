#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;
class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception()
	{
		char s[] = "Unknown exception";
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

/*//теперь наследуем ошибки от Exception
class DivisionByZero : public Exception
{
	//деление на 0
private:
	//числитель
	int numerator;

public:
	//конструктор
	DivisionByZero(int Numerator) : Exception("attempt to divide by zero")
	{
		numerator = Numerator;
	}

	//get-тер - получение числителя извне
	int getNumerator() { return numerator; }

	//вывод сообщения - переопределение виртуальной функции базового класса
	void print()
	{
		cout << "Exception: " << str << ", numerator = " << numerator << "; " << what();
		//также можно воспользоваться функцией вывода базового класса и потом дописать числитель
		//из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
		//Exception::print();
		//cout << ", numerator = " << numerator;
	}
};


class NegativeDenominator : public Exception
{
	//отрицательный знаменатель
private:
	//исходная дробь
	//числитель
	int numerator;
	//знаменатель
	int denominator;
	//значение, которое пытались установить
	int value;
public:
	//конструктор
	NegativeDenominator(int Numerator, int Denominator, int Value) : Exception("attempt to set negative denominator")
	{
		numerator = Numerator;
		denominator = Denominator;
		value = Value;
	}

	//get-теры - получение дроби извне
	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }
	//получение значения, которое пытались установить в знаменатель
	int getValue() { return value; }

	//вывод сообщения
	void print()
	{
		cout << "Exception: " << str << ", value = " << value << ", Fraction = " << numerator << "/" << denominator << "; " << what();
		//также можно воспользоваться функцией вывода базового класса и потом дописать числитель
		//из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
		//Exception::print();
		//cout << ", value = " << value << ", Fraction = "<<numerator<<"/"<<denominator;
	}
};*/

class IndexOutOfException : public Exception
{
protected:
	int row_index;
	int col_index;
public:
	IndexOutOfException(int r, int c) : Exception("Index in array is out ")
	{
		row_index = r;
		col_index = c;
	}
	IndexOutOfException(const IndexOutOfException& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
		row_index = e.row_index;
		col_index = e.col_index;
	}

	virtual void print()
	{
		cout << "IndexOutOfException: " << str << ";row_index = " << row_index;
		cout << "; col_index =" << col_index << what();
	}
};

/*class WrongDimersions : public Exception
{
protected:

public:
	WrongDimersions () : Exception("Dimersions") {}

	WrongDimersions(const WrongDimersions& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}

	virtual void print()
	{
		cout << "IndexOutOfException: " << str << ";row_index = " << row_index;
		cout << "; col_index =" << col_index << what();
	}
};*/

class WrongSize : public Exception
{
protected:
	int height;
	int width;
public:
	WrongSize() : Exception("Wrong size of matrix ")
	{
		height = 1;
		width = 1;
	}
	WrongSize(int h, int w) : Exception("Wrong size of matrix ")
	{
		height = h;
		width = w;
	}
	WrongSize(const WrongSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
		height = e.height;
		width = e.width;
	}

	virtual void print()
	{
		cout << "IndexOutOfException: " << str << ";hight = " << height;
		cout << "; wight =" << width << what();
	}
};

class NegSize : public WrongSize
{
public:
	NegSize(int h, int w) : WrongSize(h, w) {}
	NegSize(const NegSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
		height = e.height;
		width = e.width;
	}
};

class NullSize : public WrongSize
{
public:
	NullSize(int h, int w) : WrongSize(h, w) {}
	NullSize(const NullSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
		height = e.height;
		width = e.width;
	}
};

class Type_not_in : public Exception
{
protected:
public:
	Type_not_in(int r, int c) : Exception("Type_not_in"){}


	virtual void print()
	{
		cout << " Type_not_in: " << str << what();
	}
};
class BaseMatrix
{
protected:
	double** ptr;
	int height;
	int width;
	int x;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		if (Height < 0 || Width < 0)
			throw NegSize(Height, Width);
		if (Height == 0 || Width == 0)
			throw NullSize(Height, Width);
		//конструктор
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width]; // элементы с строках могут лежать не по порядку, поэтому надо сначала обращаться к i указателю, и потом отступать j позиций
		}
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
	}

	~BaseMatrix()
	{
		//деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
	}

	double& operator() (int row, int column)
	{
		if (row < 0 || column < 0 || row >= height || column >= width)
			throw IndexOutOfException(row, column);
		return ptr[row][column];
	}

	void print()
	{
		//вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
		cout << "\n";
	}

};

class Matrix : public BaseMatrix
{
protected:
	double ScalarProduct(double* arr1, double* arr2, int dim)
	{
		double sum = 0;
		for (int i = 0; i < dim; i++)
			sum += arr1[i] * arr2[i];
		return sum;
	}

public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) { };
	Matrix(const Matrix& M)
	{
		//конструктор копий
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
	}

	double Trace()
	{
		double res = 0;
		for (int i = 0; i < height; i++)
			res += ptr[i][i];
		return res;
	}

	Matrix operator+(Matrix B)
	{
		Matrix res(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				res.ptr[i][j] = ptr[i][j] + B.ptr[i][j]; // или res(i,j) = ptr[i][j] + B.ptr[i][j];
		return res;
	}

	Matrix operator+() // транспонирование 
	{
		Matrix res(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				res.ptr[j][i] = ptr[i][j];
		return res;
	}

	double* operator*(double* arr)
	{
		double* res = new double[height];
		for (int i = 0; i < height; i++)
			res[i] = ScalarProduct(ptr[i], arr, width);
		return res;
	}

	void Evklidova_norma_column()
	{
		//пузырек
		/*double sum_1, sum_2;
		for (int r = 0; r < width - 1; ++r)
		{
			sum_1 = 0;
			sum_2 = 0;
			for (int y = 0; y < height; ++y)
			{
				sum_1 += ptr[y][r] * ptr[y][r];
				sum_2 += ptr[y][r + 1] * ptr[y][r + 1];
			}
			if (sum_2 < sum_1)
			{
				for (int k = 0; k < width - 1; ++k)
					for (int t = 0; t < height; ++t)
					{
						double c;
						c = ptr[t][k];
						ptr[t][k] = ptr[t][k + 1];
						ptr[t][k + 1] = c;
					}
			}
		}*/
		//сортировка выбора
		int flag = 0;
		double sum_1, sum_2, per_min = 100000;
		int column_min = 0;
		for (int r = 0; r < width; ++r)
		{
			column_min = r;
			for (int y = r + 1; y < width; y++)
			{
				sum_1 = 0;
				sum_2 = 0;
				for (int i = 0; i < height; ++i)
				{
					sum_1 += (ptr[i][r] * ptr[i][r]);
					sum_2 += (ptr[i][y] * ptr[i][y]);

				}
				if (per_min > sum_2)
				{
					per_min = sum_2;
					if (column_min != y)
						column_min = y;
				}
			}
			if (per_min < sum_1)
			{
				for (int i = 0; i < height; ++i)
				{
					double c;
					c = ptr[i][r];
					ptr[i][r] = ptr[i][column_min];
					ptr[i][column_min] = c;

				}
			}
		}
	}

	friend ostream& operator<<(ostream& s, Matrix M); //вывод
	friend istream& operator>>(istream& s, Matrix& M); // ввод
};

ostream& operator<<(ostream& s, Matrix M)
{
	if (typeid(s) == typeid(ofstream))
	{
		// работа с файлами 
		//  сохраняем размерности
		s << M.height << " " << M.width << " ";
		// сохраняем элементы матрицы
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
	}
	else
	{
		// вывод в консоль
		int i, j;
		for (i = 0; i < M.height; i++)
		{
			for (j = 0; j < M.width; j++)
				s << M.ptr[i][j] << "\t";
			s << "\n";
		}
	}
	return s;
}

istream& operator>>(istream& s, Matrix& M)
{
	int x;
	if (typeid(s) == typeid(ifstream))
	{
		//ввод из файла
		//  читаем размерности
		int height, width;
		s >> height >> width;
		if (height < 0 || width < 0)
			throw NegSize(height, width);
		if (height == 0 || width == 0)
			throw NullSize(height, width);
		if (height != M.height || width != M.width)
			throw Exception("Wrong dimensions reading file");
		// чтение элементов матрицы
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s >> M.ptr[i][j];
	}
	else
	{
		// ввод из консоля
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s >> M.ptr[i][j];

	}
	return s;
}

/*class Fraction
{
private:
	//числитель
	int numerator;
	//знаменатель
	int denominator;
public:
	//get-теры - получение значений числителя и знаменателя извне
	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }

	//установка числителя
	void setNumerator(int value) { numerator = value; }

	//умножение
	Fraction operator*(Fraction F)
	{
		Fraction Res;
		Res.numerator = numerator * F.numerator;
		Res.denominator = denominator * F.denominator;
		return Res;
	}

	//вывод
	void print()
	{
		cout << numerator << "/" << denominator;
	}

	//конструктор
	Fraction(int Numerator = 0, int Denominator = 1)
	{
		if (Denominator == 0)
			throw DivisionByZero(Numerator);
		if (Denominator < 0)
			throw NegativeDenominator(0, 1, Denominator);

		//здесь всё хорошо
		numerator = Numerator;
		denominator = Denominator;
	}

	//set-тер для знаменателя
	void setDenominator(int value)
	{
		if (value == 0)
			throw DivisionByZero(numerator);
		if (value < 0)
			throw NegativeDenominator(numerator, denominator, value);

		//здесь всё хорошо
		denominator = value;
	}
};*/

int main()
{
	if (true)
	{
		Matrix M(3, 3);
		//cin >> M;
		M(0, 0) = 1;
		M(0, 1) = 2;
		M(1, 0) = 3;
		M(1, 1) = 4;
		M(0, 0) = 1;
		M(0, 2) = 2;
		M(1, 2) = 4;
		M(2, 1) = 2;
		M(2, 0) = 6;
		M(2, 2) = 0;

		M.print();
		//cout << M;

		cout << "\n*****Evklidova_norma_column*****\n";

		M.Evklidova_norma_column();

		M.print();

		Matrix M2(3, 4);
		//cin >> M;
		M2(0, 0) = 1;
		M2(0, 1) = 2;
		M2(1, 0) = 3;
		M2(1, 1) = 4;
		M2(0, 0) = 1;
		M2(0, 2) = 2;
		M2(1, 2) = 4;
		M2(2, 1) = 2;
		M2(2, 0) = 6;
		M2(2, 2) = 0;
		M2(0, 3) = 6;
		M2(1, 3) = 1;
		M2(2, 3) = 5;

		M2.print();
		//cout << M;

		cout << "\n*****Evklidova_norma_column*****\n";

		M2.Evklidova_norma_column();

		M2.print();

	}
	//try
	//{

	//	Matrix M(2, 2);
	//	Matrix M2(2, 2);
	//	cin >> M2;
	//	M(0, 0) = 1;
	//	M(0, 1) = 2;
	//	M(1, 0) = 5;
	//	M(1, 1) = 4;
	//	M.print();
	//	cout << M;

	//	cout << "\n*****Evklidova_norma_column*****\n";

	//	M.Evklidova_norma_column();

	//	M.print();

	//	/*Matrix Mf(2, 2);
	//	int n = 5;
	//	Matrix* arr = new Matrix[5];
	//	for (int i = 0; i < 5; i++)
	//		for (int j = 0; j < 2; j++)
	//			for (int k = 0; k < 2; k++)
	//				arr[i](j, k) = i * j * k;*/

	//	//ofstream fout("test.txt");
	//	//if (fout) // if(fout!=NULL)
	//	//{
	//	//	fout << "n" << "\n";
	//	//	for (int i = 0; i < 5; i++)
	//	//		fout << arr[i] << "\n";
	//	//	fout.close();
	//	//}
	//	//Matrix a;
	//	//ifstream fin("test.txt");
	//	//if (fin) // if(fin!=NULL)
	//	//{
	//	//	int n;
	//	//	fin >> n;
	//	//	Matrix* arr1 = new Matrix[n];
	//	//	for (int i = 0; i < n; i++)
	//	//	{
	//	//		fin >> arr1[i];
	//	//		cout << arr1[i] << "\n------\n ";
	//	//	}
	//	//	delete[] arr1;
	//	//	fin.close();
	//	//	//Стандартная операци ячтения
	//	//	while (!fin.eof())//пока не конец файла что-то читать
	//	//		fin >> a;

	//	//}
	//	//cout << Mf;
	//	//delete[] arr;
	//}
	//catch (Type_not_in e)
	//{
	//	cout << " Type_not_in:"; e.print();
	//}
	//catch (IndexOutOfException e)
	//{
	//	cout << " Exception has bee caught:"; e.print();
	//}
	//catch (WrongSize e) // может обрабатывать и производные классы
	//{
	//	cout << " Exception has bee caught:"; e.print();
	//}
	//catch (Exception e) // может обрабатывать и производные классы
	//{
	//	cout << " Exception has bee caught:"; e.print();
	//}
	//catch (exception e) // все исключения
	//{
	//	cout << " Exception has bee caught:"; e.what();
	//}
	//catch (...) // обрабатывает все типы исключений
	//{
	//} // сначала пишем дочерние catch, а потом родительские, чтобы дочерние сработали

	char c;
	char text[] = "Very long text in file"; // буквы считаются один словом до 1 пробела 
	ofstream fout("text.txt");
	if (fout)
	{
		fout << text;
		fout.close();
	}

	ifstream fin("text.txt");
	if (fin) // if(fin!=NULL)
	{
		while (!fin.eof()) // потоковая операция
		{
			char s[1024];
			fin >> s;
			cout << s << "\n";
		}

	}
	return 0;
	/* для чтения целой строки getline(...);
	 а потоковая операция читает слова
	return 0;*/
}

/*3 основные оператора:
try       обработка исключений
{ throw ...; сами генирируем исключения и сразу переходим к блоку catch}
catch (mun тип исключения)
{...} Затем переходит к обычным операциям
Работает только один catch, они различаются по типам ошибок
Самые простые исключения:
выделение памяти bad_alloc
чтение файлов
обращение к массиву с неадекватными индексами
*/
/*Наши исключения
1.IndexOutOfBeunds кривые индексы
2.WrongDimersions плохой размер матрицы для операции + и *
3.WrongSize плохой размер (отрицательный или 0)
От него отходят
3.1.NegSize и 3.2.
1, 2, 3 наследуются от весех ошибок Exception
3.1 и 3.2 наследуются от 3
Сиситема ввода и вывода
ostream& operator<<(ostream& s, Matrix M)
{
	int i, j;
	for (i = 0; i<M.heigth; i++)
	{
		for (j = 0; j<M.width; j++)
			s<<M.ptr[i][j]<< "\t";
		s<<"\n";
	}
	return s;
}
1.istream
2.ostream
3.ifstream
4.ofstream
1 и 2 от stream
3 от 1
4 от 2
int a = 5;
int b = a<<4; побитовый сдвиг, быстрое возведение в степень двойки
получаем b = 5*2^4
*/
/*Массив из матриц
* храним кол-во матриц
* 2
* 22 1234
* 13 123
*
*/
/*eof - конец файла
while (!fin.eof()) пока не конец файла что-то читать
	fin >> a;
	cout<<a<<"\n";
*/
/*преобразование типов
double d=5
int  n = 15;
d = (double)n; может делат автоматически, т.к. double больше, чем int
n = (int)d;

d = static_cast<double>(n);
n = static_cast<int>(d);

Преобразование от базового класса в дочернему
void HandleMatrix(BaseMatrix* ptr)
{
	if (typeid(*ptr) == typeid(Matrix)) обязательно звездочка
	{
		Matrix* p = dynamic_cast<Matrix*>(ptr);  указатель типа производного класса
		cout << *p ; внутри BaseMatrix должда быть >= 1 виртуальной функции (можно сделать виртуальной print)
	}
}

main
{
	BaseMatrix *p;
	Matrix M;
	p = &M;
	HandleMatrix(p);
	cout<<M;
	cout<<*p; не можем написать, тк нет такой операции в BaseMatrix, а указатель у нас именно этого класса, а после переопределения можно
}
Если у нас была виртуальная функция в производном классе, то выполняется именно она
*/

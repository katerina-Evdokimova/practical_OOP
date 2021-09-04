# practical_c++
Решение задач по ООП 1 курса 2 семестра.

## Практика 1

[Практика 1](https://github.com/katerina-Evdokimova/practical_OOP/blob/main/Practical_1.cpp)
Изучена перегрузка операций.
Сложение с вектором из 3 компонент, вычитание двух точек - вектор.

```Cpp

class Vector
{
protected:
	
	double x;
	double y;
	double z;
public:
	
	Vector() { x = 0; y = 0; z = 0; }
	Vector(double X) { x = X; y = 0; z = 0; }
	Vector(double X, double Y) { x = X; y = Y; z = 0; }
	Vector(double X, double Y, double Z) { x = X; y = Y; z = Z; }
	Vector(Vector& F) { x = F.x; y = F.y; z = F.z; }
	
	~Vector() { cout << "Destructor is working" << endl; }

	Vector operator+(Vector F)
	{
		Vector Res;
		Res.x = x + F.x;
		Res.y = y + F.y;
		Res.z = z + F.z;

		return Res;
	}

	Vector operator-(Vector F) 
	{
		Vector Res;
		Res.x = x - F.x;
		Res.y = y - F.y;
		Res.z = z - F.z;
		return Res;
	}
	void print()
	{
		std::cout <<"{ "<< x << ", " << y << ", " << z << " }" << endl;
	}
};

class Vector_Child : public Vector
{
public:

	Vector_Child() : Vector() {}
	Vector_Child(double X) : Vector(X){}
	Vector_Child(double X, double Y) : Vector(X, Y) {}
	Vector_Child(double X, double Y, double Z) : Vector(X, Y, Z){}
	Vector_Child(Vector& F) : Vector(F) {}

	~Vector_Child() { cout << "\nVector_Child destructor\n"; }

	Vector_Child operator+(Vector_Child F)
	{
		Vector_Child Res;
		Res.x = x + F.x;
		Res.y = y + F.y;
		Res.z = z + F.z;

		return Res;
	}

	Vector_Child operator-(Vector_Child F)
	{	
		Vector_Child Res;
		Res.x = x - F.x;
		Res.y = y - F.y;
		Res.z = z - F.z;
		return Res;
	}
	

	friend Vector_Child operator+(int a, Vector_Child F);
	friend Vector_Child operator+(Vector_Child F, int a);

	
};

Vector_Child operator+(Vector_Child F, int a)
{
	Vector_Child Res;
	Res.x = a + F.x;
	Res.y = a + F.y;
	Res.z = a + F.z;

	return Res;

}
Vector_Child operator+(int a, Vector_Child F)
{
	Vector_Child Res;
	Res.x = a + F.x;
	Res.y = a + F.y;
	Res.z = a + F.z;

	return Res;

}
```
## Практика 2

Реализовае бинарный поиск и поиск по индексу.

[Практика 2](https://github.com/katerina-Evdokimova/practical_c-/blob/main/Practical_2.cpp)

## Практика 3

[Практика 3](https://github.com/katerina-Evdokimova/practical_OOP/blob/main/Practical_3.cpp)

Реализовано наследование вида:

![](https://sun9-20.userapi.com/impg/jJaWEDUd17y5fzsy1I2tkH84kgwKLTVHERXZXw/N9qxrxj67IU.jpg?size=649x622&quality=96&sign=86febb1c61f96121d838fab3e53b2022&type=album "Орк")

## Практика 4

Работа со строками. Сравнение строк.

[Практика 4](https://github.com/katerina-Evdokimova/practical_OOP/blob/main/Practical_4.cpp)

## Практика 5

[Практика 5](https://github.com/katerina-Evdokimova/practical_OOP/blob/main/Practical_5.cpp)

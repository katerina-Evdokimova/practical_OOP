# practical_c++
Решение задач по ООП 1 курса 2 семестра.

## Практика 1

Реализован класс Vector:

```{C++}< >{class Vector
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
}```


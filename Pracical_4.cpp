#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(const char* ptr)
	{
		cout << "\nBase Constructor 1\n";
		if (ptr != NULL)
		{
			int i = 0;
			while (ptr[i] != '\0')
				i++;
			len = i + 1;

			capacity = 256 > len ? 256 : len;
			p = new char[capacity];

			for (i = 0; i < len; i++)
				p[i] = ptr[i];
			p[i] = '\0';
		}
	}

	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) { return p[i]; }


	BaseString& operator=(BaseString& s)
	{
		cout << "\nBase Operator = \n";
		if (s.p != NULL)
		{
			int i = 0;
			len = s.len;

			capacity = 256 > len ? 256 : len;// это единтсвенная тернарная операция (с 3 операторами)
			p = new char[capacity];

			for (i = 0; i < s.len; i++)
				p[i] = s.p[i];
			p[i] = '\0';
		}
		return *this;
	}

	BaseString operator+(BaseString s)
	{
		cout << "\nBase Operator = \n";
		int res_len = len + s.len + 1 > 256 ? len + s.len + 1 : 256;
		BaseString Res(res_len);

		int i;
		for (i = 0; i < len; i++)
			Res[i] = p[i];
		for (i = 0; i < s.len; i++)
			Res[i + len - 1] = s.p[i];
		Res[len + s.len] = '\0';
		Res.len = len + s.len;
		return Res;
	}

	BaseString(BaseString& s)
	{
		cout << "\nBase Copy Constructor\n";
		if (s.p != NULL)
		{
			int i = 0;
			len = s.len;

			capacity = 256 > len ? 256 : len;
			p = new char[capacity];

			for (i = 0; i < s.len; i++)
				p[i] = s.p[i];
			s.p[i] = '\0';
		}
	}

	virtual void print()
	{
		int i = 0;
		while (p[i] != '\0')
		{
			cout << p[i];
			i++;
		}
	}
};

class String : public BaseString
{
public:
	String(const char* ptr) : BaseString(ptr) { cout << "\nString Constructor 1\n"; }

	String(int Capacity = 256) : BaseString(Capacity)
	{
		cout << "\nString Constructor 0\n";
	}

	String(String& t)
	{
		cout << "\nBase Copy Constructor\n";
		if (t.p != NULL)
		{
			int i = 0;
			len = t.len;

			capacity = 256 > len ? 256 : len;
			p = new char[capacity];

			for (i = 0; i < t.len; i++)
				p[i] = t.p[i];
			t.p[i] = '\0';
		}
	}

	String& operator=(String& t)
	{
		cout << "\nString Operator = \n";

		BaseString& ret = (BaseString&)t;
		BaseString::operator=(ret);
		return *this;
	}

	~String() { cout << "\nString Destructor\n"; }

	bool Palindrome()
	{
		char* p1 = p;
		// *(p+i) = обращение к i элементу или *(i+p), или i[p]
		char* p2 = &p[len - 2];

		while (p1 < p2)
		{
			if (*p1 != *p2)
				return false;
			*p1++;
			*p2--;
		}
		return true;

	}

	bool comparison(String F)
	{
		int lenght = F.len;
		for (int i = 0; i < len; i++)
		{ 
			//// функция tolower(x) - преобразует x в нижний регистр
			////Следовательно, этот вариант регистронезависисимый.
			//if (tolower(p[i]) >= tolower(F[i])) { return false; }
			//else return true;
			p[i] = p[i] > 97 ? p[i] : p[i] + 32; // сравниваем по ASCII, если значение больше 97(следовательно, буквы маленькие), то оставляем
			// иначе добавляем 32 и переводим букву в другой регистр.
			F[i] = F[i] > 97 ? F[i] : F[i] - 32;
			if (p[i] >= F[i]) { return false; }
			else return true;

		}

		return true;
	}
};


int main()
{

	if (true)
	{
		String p("AAA");
		p.print();
		String s("bbb");
		s.print();

		if (s.Palindrome() == true)
			cout << "\nPalendrom";
		else
			cout << "\nnot Palendrom";

		if (p.comparison(s) == true)
			cout << "\n***TRUE***";
		else
			cout << "\n***FALSE***";

	}
	char c; cin >> c;
	return 0;
}

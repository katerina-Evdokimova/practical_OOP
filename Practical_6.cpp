using namespace std;

#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


template<class T>
class Element
{
	//protected:
public:
	//ïåðåìåñòèòü â protected
	Element* next;
	Element* prev;
	T info;

	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T>
class LinkedList
{
	//protected:
public:
	//ïåðåìåñòèòü â protected
	Element<T>* head;
	Element<T>* tail;
	int count;

	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T* arr, int len)
	{
		//...
	}

	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(T value) = 0;

	Element<T>& operator[](int index)
	{
		//if(index<0 || index>=count) throw ?;

		Element<T>* current = head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->next, i++);

		return *current;
	}

	void push_back(T value)
	{
		if (head != NULL)	//count==0
		{
			//íå ïóñòîé ñïèñîê
			tail->next = new Element<T>(value);
			tail->next->next = NULL;
			tail->next->prev = tail;
			tail = tail->next;
			count++;
		}
		else
		{
			//ïóñòîé ñïèñîê
			head = new Element<T>(value);
			head->next = NULL;
			head->prev = NULL;
			tail = head;
			count++;
		}
	}

	virtual bool isEmpty() { return (LinkedList<T>::count == 0); }

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);

	virtual ~LinkedList()
	{
		cout << "\nLinkedList class destructor";

		Element<T>* current = head;
		Element<T>* nextelem;
		while (current != NULL)
		{
			nextelem = current->next;
			delete current;
			current = nextelem;
		}

		head = tail = NULL;
		count = 0;
	}
	Element<T>* insert(Element<T>* current, T value)
	{
		if (current == NULL)
		{
			//push_front(value);
			return head;
		}
		if (current == tail)
		{
			push_back(value);
			return tail;
		}
		Element<T>* inserted = new Element<T>(value);
		Element<T>* old_next = current->next;

		current->next = inserted;
		inserted->prev = current;	//current->next->prev

		inserted->next = old_next;
		old_next->prev = inserted;

		return inserted;
	}

	Element<T>* find(T value) {
		auto current = head;
		while (current != NULL && current->info != value) {
			current = current->next;
		}
		return current;
	}
};

template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	for (current = el.head; current != NULL; current = current->next)
		s << *current << "; ";
	return s;
}

class my_class
{
public:
	int data;
	my_class(int v = 0) { data = v; }

	~my_class() { cout << "\nmy_class destructor"; }

	friend ostream& operator<<(ostream& s, my_class& value);

};

ostream& operator<<(ostream& s, my_class& value)
{
	s << value.data;
	return s;
}

bool f(int value)
{
	if (value % 3 == 0) return true;
	return false;
}

template<class T>
class Queue : public LinkedList<T>
{
public:
	Queue<T>() : LinkedList<T>() {}
	Queue<T>(T* arr, int len) : LinkedList<T>(arr, len) {}
	virtual ~Queue() { cout << "\nQueue class destructor"; }

	virtual Element<T>* push(T value)
	{
		Element<T>* element = new Element<T>(value);

		if (LinkedList<T>::tail == NULL)
		{
			LinkedList<T>::tail = LinkedList<T>::head = element;
		}
		else
		{
			LinkedList<T>::tail->next = element;
			LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
			LinkedList<T>::tail = LinkedList<T>::tail->next;
		}

		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}

	virtual Element<T>* pop()
	{

		if (LinkedList<T>::head == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::head;
		if (LinkedList<T>::head == LinkedList<T>::tail)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
		{
			LinkedList<T>::head->next->prev = NULL;
			LinkedList<T>::head = LinkedList<T>::head->next;
			res->next = NULL;
		}

		LinkedList<T>::count--;
		return res;
	}

	void Filtez(Queue<T>* Res, bool (*p)(T))
	{
		for (Element<T>* current = LinkedList<T>::head; current != NULL; current = current->next)
			if (p(current->info) == true)
				Res->push(current->info);
	}

	Element<T>* Find_r(T value, Element<T>* current = NULL /*ãäå ìû íàõîäèìñÿ*/)
	{
		//current == NULL - ïîèñê ïî âñåìó ñïèñêó, íî íàäî áûòü îñòîðîæíûì ñ êîíöîì
		if (LinkedList<T>::head == NULL) return NULL;
		if (current == NULL) current = LinkedList<T>::head;
		if (current->info == value) return current;
		else
		{
			if (current->next != NULL)
				return Find_r(value, current->next);
			else
				return NULL;
		}
	}

	void print(Element<T>* current)
	{
		if (current == NULL) current = LinkedList<T>::head;
		cout << current->info << ", ";
		if (current->next != NULL)
			print(current->next);
	}
};

class Date {
public:
	int year;
	int mounth;
	int day;
	Date(int d = 1, int m = 1, int y = 2000) {
		day = d;
		mounth = m;
		year = y;
	}
	friend ostream& operator<<(ostream& s, const Date& d);
	friend istream& operator>>(ostream& s, const Date& d);
};

ostream& operator<<(ostream& s, const Date& d) {
	if (typeid(s) == typeid(ofstream)) {
		s << d.day << " " << d.mounth << " " << d.year;
	}
	else {
		s << d.day << "." << d.mounth << "." << d.year;
	}

	return s;
}

istream& operator>>(istream& s, Date& d) {
	if (typeid(s) == typeid(ifstream)) {
		string line;
		getline(s, line);
		std::istringstream iss(line);
		iss >> d.day >> d.mounth >> d.year;

	}
	s >> d.day >> d.mounth >> d.year;
	return s;
}

class Schoolboy
{
public:
	string surname;
	string name;
	string gender;
	Date birth;
	string address;
	int School_class;

	Schoolboy(string surname_s = " ", string name_s = " ", string gender_s = " ", Date birth_s = Date(), string address_s= " ", int School_class_s = 1)
	{
		surname = surname_s;
		name = name_s;
		birth = birth_s;
		address = address_s;
		School_class = School_class_s;
	}

	Schoolboy(const Schoolboy& p) 
	{
		surname = p.surname;
		name = p.name;
		birth = p.birth;
		address = p.address;
		School_class = p.School_class;
	}
	Schoolboy& operator=(const Schoolboy& p) 
	{
		surname = p.surname;
		name = p.name;
		birth = p.birth;
		address = p.address;
		School_class = p.School_class;
		return *this;
	}

	~Schoolboy(){}

	friend ostream& operator<<(ostream& s, const Schoolboy& p);
	friend istream& operator>>(istream& s, const Schoolboy& p);
};

ostream& operator<<(ostream& s, const Schoolboy& p)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << p.surname << "\n" << p.name << "\n" << p.birth << "\n" << p.address << "\n" << p.School_class;
	}
	else
	{
		s << "Surname: " << p.surname << "\nName: " << p.name << "\nDate of birth: " << p.birth << "\nAddress: "<< p.address << "\nClass number: " << p.School_class;

	}
	return s;
}

istream& operator>>(istream& s, Schoolboy& p) {
	if (typeid(s) == typeid(ifstream)) {

		string line;


		getline(s, p.surname);
		getline(s, p.name);

		getline(s, line);
		std::istringstream iss1(line);
		iss1 >> p.birth;

		getline(s, p.address);

		getline(s, line);
		std::istringstream iss3(line);
		iss3 >> p.School_class;
	}
	else {
		cout << "Bad Readed:\n" << p << endl;
		s >> p.surname >> p.name >> p.birth  >> p.address >> p.School_class;
	}

	return s;
}
template <class T>
class unification : public LinkedList<T>
{
public:
	unification() : LinkedList<T>() {}

	virtual ~unification() 
	{
		cout << "Destr";
		Element<T>* cur = this->head;
		while (cur != nullptr) {
			Element<T>* to_delete = cur;
			cur = cur->next;
			delete to_delete;
		}
		this->head = nullptr;
		this->count = 0;
		this->head = nullptr;
	}

	unification(const unification& value)
	{
		this->count = 0;
		Element<T>* cur_in = value.head;
		Element<T>* cur_this = nullptr;
		while (cur_in != nullptr)
		{

			if (cur_this == nullptr) 
			{
				cur_this = new Element<T>(*cur_in);
				this->head = cur_this;
				cur_in = cur_in->next;
			}
			else 
			{
				cur_this->next = new Element<T>(*cur_in);
				cur_this->next->prev = cur_this;
				cur_this = cur_this->next;
				cur_in = cur_in->next;
			}
			++(this->count);
		}
		this->tail = cur_this;
	}

	unification& operator=(const unification& value)
	{
		this->clear();
		this->count = 0;
		Element<T>* cur_in = value.head;
		Element<T>* cur_this = nullptr;
		while (cur_in != nullptr) {

			if (cur_this == nullptr) {
				cur_this = new Element<T>(*cur_in);
				this->head = cur_this;
				cur_in = cur_in->next;
			}
			else {
				cur_this->next = new Element<T>(*cur_in);
				cur_this->next->prev = cur_this;
				cur_this = cur_this->next;
				cur_in = cur_in->next;
			}
			++(this->count);
		}
		this->tail = cur_this;
		return *this;
	}

	virtual Element<T>* insert(Element<T>* current, T value)
	{
		if (current == NULL)
		{
			//push_front(value);
			return LinkedList<T>::head;
		}
		if (current == LinkedList<T>::tail)
		{
			push_back(value);
			return LinkedList<T>::tail;
		}

		Element<T>* inserted = new Element<T>(value);
		Element<T>* old_next = current->next;

		current->next = inserted;
		inserted->prev = current;	//current->next->prev

		inserted->next = old_next;
		old_next->prev = inserted;

		return inserted;
	}

	virtual void push_back(T value)
	{
		if (LinkedList<T>::head != NULL)	//count==0
		{
			//íå ïóñòîé ñïèñîê
			LinkedList<T>::tail->next = new Element<T>(value);
			LinkedList<T>::tail->next->next = NULL;
			LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
			LinkedList<T>::tail = LinkedList<T>::tail->next;
			LinkedList<T>::count++;
		}
		else
		{
			//ïóñòîé ñïèñîê
			LinkedList<T>::head = new Element<T>(value);
			LinkedList<T>::head->next = NULL;
			LinkedList<T>::head->prev = NULL;
			LinkedList<T>::tail = LinkedList<T>::head;
			LinkedList<T>::count++;
		}
	}

	virtual Element<T>* push(T value)
	{
		Element<T>* element = new Element<T>(value);

		if (LinkedList<T>::tail == NULL)
		{
			LinkedList<T>::tail = LinkedList<T>::head = element;
		}
		else
		{
			LinkedList<T>::tail->next = element;
			LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
			LinkedList<T>::tail = LinkedList<T>::tail->next;
		}

		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}

	/*virtual Element<T>* find(T value) {
		auto current = LinkedList<T>::head;
		while (current != NULL && current->info != value) {
			current = current->next;
		}
		return current;
	}*/


	virtual Element<T>* pop()
	{

		if (LinkedList<T>::head == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::head;
		if (LinkedList<T>::head == LinkedList<T>::tail)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
		{
			LinkedList<T>::head->next->prev = NULL;
			LinkedList<T>::head = LinkedList<T>::head->next;
			res->next = NULL;
		}

		LinkedList<T>::count--;
		return res;
	}

	template <class T1>
	unification filter(bool (*p)(const T& comparison, const T1 param), const T1 value)
	{
		unification<T> Res;
		Element<T>* curent = this->head;
		while (curent != nullptr) 
		{
			if (p(curent->info, value)) 
			{
				Res.push(curent->info);
			}
			curent = curent->next;
		}
		return Res;
	}

	void save(ofstream& s)
	{
			s << this->count << endl;
			Element<T>* cur = this->head;
			for (int i = 0; i < this->count; ++i) 
			{
				s << (*cur) << endl;
				cur = cur->next;
			}
	}

	void load(ifstream& s)
	{
			int count;
			string line;
			getline(s, line);
			std::istringstream iss(line);
			iss >> count;
			for (int i = 0; i < count; ++i)
			{
				T cur;
				s >> cur;
				this->push(cur);
			}
	}

	void print()
	{
		while (!this->isEmpty())
		{
			Element<T>* ptr = this->pop();
			cout << ptr->info << "\n";
			delete ptr;
		}
	}
	friend ostream& eight(ostream& stream);
};

//ìàíèïóëÿòîð
ostream& eight(ostream& stream)
{
	stream.setf(ios::left); //âûðàâíèâàíèå ïî ëåâîìó êðàþ
	stream << oct;
	return stream;
}

bool contrast(const Schoolboy& p, string value = "")
{
	if (p.surname == value) return true;
	return false;
}

bool filter_class(const Schoolboy& p, int cl = 1) 
{
	if (p.School_class <= cl) return true;
	return false;
	
}
int factorial(int n)
{
	if (n > 2) return n * factorial(n - 1);
	if (n == 0 || n == 1) return 1;
	if (n == 2) return 2;
}



int main()
{
	if (true)
	{
		unification<Schoolboy> s;
		s.push(Schoolboy());
		s.push(Schoolboy("Evdokimova"));
		s.push(Schoolboy("OOOOOOO"));

		//s.remove(1);

		//s.insert(Schoolboy("tttt"), 2);
		unification<Schoolboy> s2 = s.filter(contrast, string("Evdokimova"));
		string file_name = "test1.txt";
		ofstream fout(file_name);

		if (fout.is_open()) {
			s.save(fout);
			fout.close();
		}
		else {
			std::cout << "file not opened\n";
		}

		ifstream fin(file_name);

		if (fin.is_open()) {
			s.load(fin);
			fin.close();
		}
		else {
			std::cout << "file not opened\n";
		}
		cout << "\n~~~Readed from file~~~\n";
		s.print();

		s2.print();

		
		cout << "\n~~~Vosmer~~~\n";
		//eight(cout);
		unification<Schoolboy> s4;
		Schoolboy p;
		p = Schoolboy("KArmi", "Olga", "woman", Date(10, 9, 207), "Trefjh ", 14);

		//s4.print();

		cout << eight << "Surname: " << p.surname << "\nName: " << p.name << "\nDate of birth: " << p.birth << "\nAddress: " << p.address <<"\nClass number: " << p.School_class;
		//s4.print();
		cout << "\n~~~No cast~~~\n";
		LinkedList<Schoolboy>* base_class_ptr = new unification<Schoolboy>;
		delete base_class_ptr;

		cout << "\n~~~dynamic_cast~~~\n";
		LinkedList<Schoolboy>* ptr_to_cast = new unification<Schoolboy>;
		unification<Schoolboy>* casted = dynamic_cast<unification<Schoolboy>*>(ptr_to_cast);
		casted->print();
		delete casted;
	}

	

	/*if (true)
	{
		cout << "Only object\n";
		Queue<int> Q;
		for (int i = 0; i < 100; i += 5)
			Q.push(i);
		cout << Q;
		Queue<int>* R = new Queue<int>;
		bool (*ptr)(int);
		ptr = f;
		Q.Filtez(R, ptr);
		cout << "\n-----\n" << *R;
		delete R;
		cout << "\n" << Q.Find_r(5, 0) << "\n";
		cout << "\n******\n";
		Q.print(0);
		cout << "\n******\n";
		for (; !Q.isEmpty(); cout << Q.pop()->info << ", ");
		cout << "\n";
	}*/

	/*if (true)
	{
		cout << "\nBase pointer 1\n";
		LinkedList<int>* ptr = new Queue<int>;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//äîáàâèòü âèðòóàëüíûå äåñòðóêòîðû
	}

	if (true)
	{
		cout << "\nBase pointer 2\n";
		LinkedList<int>* ptr; Queue<int>* ptr2 = new Queue<int>; ptr = ptr2;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//äîáàâèòü âèðòóàëüíûå äåñòðóêòîðû
	}

	if (true)
	{
		cout << "\nQueue pointer\n";
		Queue<int>* ptr = new Queue<int>;
		for (int i = 2; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
	}

	if (true)
	{
		cout << "\nmy_class Queue test\n";
		Queue<my_class> Q;
		for (int i = 3; i < 100; i += 5)
			Q.push(my_class(i));
		cout << Q;
	}*/
	char c; cin >> c;
	return 0;
}


#include<iostream>
using namespace std;


class A1
{
protected:
    int a1;
public:
    A1(int V1 = 0) { a1 = V1; cout << "\nClass A1 constructor"; }
   
    virtual void print() { cout << "\nVariable of A1 class"; }
    virtual void show() { cout << "\na1 = " << a1; }
};


class B1: virtual public A1
{
protected:
    int b1;
public:
    B1(int V1 = 0, int V2 = 0) : A1(V2) { b1 = V1; cout << "\nClass B1 constructor"; }
    virtual void print() { cout << "\nVariable of B1 class"; }
    virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1; }
};


class B2 : virtual public A1
{
protected:
    int b2;
public:
    B2(int V1 = 0, int V2 = 0) : A1(V2) { b2 = V1; cout << "\nClass B2 constructor"; }
    virtual void print() { cout << "\nVariable of B2 class"; }
    virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1; }
};


class B3 : virtual public A1
{
protected:
    int b3;
public:
    B3(int V1 = 0, int V2 = 0) : A1(V2) { b3 = V1; cout << "\nClass B3 constructor"; }
    virtual void print() { cout << "\nVariable of B2 class"; }
    virtual void show() { cout << "\nb3 = " << b3 << ", a1 = " << a1; }
};


class C1 : virtual public B2, virtual public B1, virtual public B3
{
protected:
    int c1;
public:
    C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0) : A1(V5), B1(V2), B2(V3), B3(V4) { c1 = V1; cout << "\nClass B3 constructor"; }
    virtual void print() { cout << "\nVariable of C1 class"; }
    virtual void show() { cout << "\na1 = " << a1 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", c1 = " << c1;}
};

int main()
{
    C1 t(7, 8, 9, 10, 7);
    B1 test(1, 2);
    test.show();
    test.print();
    /*B2 test_1(3, 4);
    test_1.show();
    test_1.print();*/
    /*B3 test_2(5, 6);
    test_2.show();
    test_2.print();*/
    //A1* ptr = &t;
    A1 z(90);
    B2 rt(67, 56);
    rt.show();
    rt.print();
    C1 y;
    y.show();
    y.print();

    A1 * ptr = &t;
    ptr->show();
    ptr->print();
    /*Variable of C1 class
      a1 = 0, b1 = 8, b2 = 9, b3 = 10, c1 = 7
      Variable of C1 class*/
    /*Из-за наследования в форме ромба возникает неоднозначность при обращении к полям, поэтому в значении а1 получается 0
    C++ по умолчанию не создает ромбовидного наследования: компилятор обрабатывает каждый путь наследования отдельно, в результате чего объект C
    будет на самом деле содержать три разных подобъекта A1, и при использовании членов A1 потребуется указать путь наследования (B1::A1,B2::A1 and B3::A1 ) или
    необходимо сделать наследование virtual, тогда путь становится единым => в А1 передаются значения, но так как в классе С1 мы не  указывали значение
    для А1 то мы получили значение, которое стоит по умолчанию, то есть 0*/
    char c; std::cin >> c;

    return 0;
}

#include <iostream>
#include <iostream>
#include <string>
using namespace std;

struct A {
public :
    A() {
        cout << "A 생성자" << endl;
    }

    virtual ~A() {
        cout << "A 소멸자" << endl;
    }

    virtual void Print() {
        cout << "A::Print() " << endl;
    }
};

class B : public A{
public:
    B() :A() {
        cout << "B 생성자" << endl;
    }
    
    ~B() {
        cout << "B 소멸자" << endl;
    }

    void Print() override {
        A::Print();
        cout << "B::Print() "<< endl;
    }
};

class Book {
public:
    Book(string n, string a, int p) : name(n), author(a), price(p) {}

    string name;
    string author;
    int price;
    string publisDate;
};

void PrintBookInfo(Book* book) {
    cout << "책 이름: " << book->name << endl;
    cout << "책 저자: " << book->author << endl;
    cout << "가격: " << book->price << endl;
    cout << "출판 날짜 : " << book->publisDate << endl;
}

void main()
{
    A* a = new B();
    a->Print();

    delete a;

    int num;
    cin >> num;
}
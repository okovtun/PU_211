#include<iostream>
using namespace std;

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Адрес строки в динамической памяти
public:
	explicit String(int size = 256)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "Default1ArgConstruct:\t" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destrutor:\t\t" << this << endl;
	}

	//			Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

//#define CONSTRUCTORS_CHECK
#define HOME_WORK_1

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str1;		//Default constructor
	str1.print();

	//Single-argiment constructor:
	//String str2 = 16;	//explicit constructor невозможно вызвать оператором =,
	String str2(16);	//его можно вызвать только так
	str2.print();

	//https://legacy.cplusplus.com/doc/tutorial/operators/
	String str3 = "Hello";
	str3.print();
#endif // CONSTRUCTORS_CHECK

#ifdef HOME_WORK_1
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;
	cout << str1 << " + " << str2 << " = " << str3 << endl;
#endif // HOME_WORK_1

}
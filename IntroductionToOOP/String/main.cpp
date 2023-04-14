#include"String.h"

//#define CONSTRUCTORS_CHECK
#define HOME_WORK_1
//#define ISTREAM_OPERATOR
//#define CONSTRUCTORS_CHECK_2

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
	str3 = str3;
	str3.print();

	//String str4 = str3;	//Copy constructor
	String str4;
	str4 = str3;	//CopyAssignment
	str4.print();
#endif // CONSTRUCTORS_CHECK

#ifdef HOME_WORK_1
	String str1 = "Hello";
	String str2 = "World";
	//String str3 = str1 + str2;	//Move constructor
	//String str3;
	//str3 = str1 + str2;	//Move assignment
	//cout << str1 << " + " << str2 << " = " << str3 << endl;
	str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
	cout << delimiter << endl;

	String str3 = str1;
	str3.print();
#endif // HOME_WORK_1

	//Move-методы:
	//Move constructor
	//Move assignment
	//r-value reference Class&& obj
	//Shallow copy

#ifdef ISTREAM_OPERATOR
	String last_name;
	String first_name;
	//str.print();
	cout << "Введите Ваше имя: ";

	cin >> last_name >> first_name;

	//str.print();
	cout << last_name << " " << first_name << endl;
#endif // ISTREAM_OPERATOR

#ifdef CONSTRUCTORS_CHECK_2
	String str1;			//Default constructor
	str1.print();
	String str2(8);			//Single-argument constructor of type 'int'
	str2.print();
	String str3 = "Hello";	//Single-argument constructor of type 'const char*'
	str3.print();
	String str4();			//Здесь НЕ вызывается конструктор по умолчанию,
							//В этой строке объявляется функция str4, которая 
							//ничего не принимает, и возвращает значение типа String.
	//str4.	//This is not an object
	String str5{};		//Явный вызов конструктора по умолчанию
	str5.print();

	String str6{ 123 };
	str6.print();

	String str7{ "World" };
	str7.print();
#endif // CONSTRUCTORS_CHECK_2

}
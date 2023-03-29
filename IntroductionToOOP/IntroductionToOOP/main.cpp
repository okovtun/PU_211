//IntroductionToOOP
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Point
{
	/*
		Создавая структуру или класс мы создаем новый тип данных.
	*/
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//				Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "Constructor:\t" << this << endl;
	}*/
	/*Point(double x)
	{
		this->x = x;
		y = 0;
		cout << "1ArgConstructor:" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Methods:
	double distance(Point other)
	{
		//this  - эта точка
		//other - другая точка (указанная точка)
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		return distance;
	}
	void print()
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

double distance(Point A, Point B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	return sqrt(x_distance*x_distance + y_distance * y_distance);
}

//#define STRUCT_POINT
//#define DISTANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	//type name;
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Объявление объекта 'A' типа 'Point'
				//Создание экземпляра 'A' структуры 'Point'
				//Instance - экземпляр.
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	//cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B;
	B.set_x(7);
	B.set_y(8);
	//cout << B.get_x() << "\t" << B.get_y() << endl;
	B.print();

	cout << "Расстояние от точки A до точки B: " << A.distance(B) << endl;
	cout << "Расстояние от точки B до точки A: " << B.distance(A) << endl;
	cout << "Расстояние между точками A и B:   " << distance(A, B) << endl;
	cout << "Расстояние между точками B и A:   " << distance(B, A) << endl;
#endif // DISTANCE_CHECK

	Point A;	//Default constructor
	A.print();

	Point B = 5;
	B.print();

	Point C(2, 3);
	C.print();
}

/*
------------------------------------------------
.  - Оператор прямого доступа (Point operator)
-> - Оператор косвенного доступа (Arrow operator)
------------------------------------------------
*/

/*
------------------------------------------------
1. Encapsulation;
   Encapsulation - это сокрытие определенной части класса от внешнего мира.
	Модификаторы доступа:
		private:	закрытые поля, доступные только внутри класса
		public:		открытые поля, доступные из любого места программы
		protected:	защищенные поля, доступны только внутри класса, и его дочерних классов.
	get/set-методы:
		get (взять, получить) - открывает доступ к закрытым полям на чтение, т.е.,
					позволяет или взять или получить значение закрытой переменной.
		set (задать, установить) - открывает доступ к закрытым переменным на запись, т.е.,
					позволяет задавать значения закрытых переменных.
					Кроме того, set-методы обеспечивают фильтрацию данных, т.е.,
					предотвращают попадание некорректных значений в переменные члены класса.
2. Inheritance;
3. Polymorphism;
------------------------------------------------
*/

/*
------------------------------------------------
1. Constructor - это метод, который создает объект.
   Он выделяет память под объект, и инициализирует его поля при создании.
	-С парметрами;
	-Без параметров;
	-По умолчанию (Default constructor) - это конструктор, который может быть вызван без параметров;
	-Конструктор копирования;
	-Конструктор переноса;

2. ~Destructor - это метод, который уничтожает отбъект по завершении его времени жизни;

3. Assignment operator;
------------------------------------------------
*/
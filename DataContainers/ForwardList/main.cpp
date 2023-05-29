#include<iostream>
#include<string>
#include<time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

/*
--------------------------
Class obj;			//создаем объект обычного класса
Class<DataType>	obj;//создаем объект шаблонного класса
	  DataType может быть как шаблонным, так и конкретным типом данных.
ForwardList<int> list;	//Односвязный список 'int-ов'
--------------------------
*/

template<typename T>class Iterator;
template<typename T>class ForwardList;

template<typename T>	//T - имя шаблонного типа
class Element
{
	T Data;				//значение элемента
	Element<T>* pNext;	//адрес следующего элемента
	static int count;	//счетчик элементов
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};
template<typename T>
int Element<T>::count = 0;	//Статическую переменную можно проинициализировать только за пределами класса.

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}
	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)
	{
		Iterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	
	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T>
class ForwardList
{
	Element<T>* Head;	//Голова - это указатель на начальный элемент списка,
	//так же как в массиве, имя массива содержит адрес нулевого элмента,
	//Голова списа содержит адрес начального элемента.
	unsigned int size;	//Количество элементов списка
public:
	Iterator<T> begin()const
	{
		return Head;
	}
	Iterator<T> end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;	//Когда список пуст, его Голова указывает на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<T>& il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end()   - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		*this = other;	//Повторно используем код оператора =
		cout << "CopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList<T>&& other) :ForwardList()
	{
		*this = std::move(other);	//Встроенная функция std::move() принудительно вызывает MoveAssignment для своего параметра
		cout << "MoveConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		//Deep copy:
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_front(Temp->Data);
		reverse();
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(T Data)
	{
		/*
		Element* New = new Element(Data);	//1) Создаем новый элемент
		New->pNext = Head;	//2) Включаем новый элемент в список
		Head = New;		//3) Переносим Голову на новый элемент
		*/

		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(T Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//3) Включаем созданный элементв список:
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		Element<T>* Erased = Head;	//1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2) Исключаем удаляемый элемент из списка
		delete Erased;			//3) Удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void reverse()
	{
		ForwardList<T> reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
			size++;
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print()const
	{
		/*
		-----------------------
		Для того чтобы перемещаться по списку нужно две вещи:
			1. Итератор;
			2. Цикл;
		-----------------------
		*/
		cout << "\n-----------------" << this << "-----------------\n";
		cout << "Head: " << Head << endl;
		/*Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}*/

		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов:  " << Head->count << endl;
	}
};

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (Iterator<T> it = right.begin(); it != right.end(); ++it)
		cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define COPY_CHECK
//#define PREFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		//cout << number << tab;
		//list.push_front(number);
		list.push_back(number);
	}
	//list.push_back(123);
	list = list;
	list.print();
	//list.pop_back();
	int value;
	int index;

	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	list.insert(value, index);
	list.print();


	/*ForwardList list2;
	list2.push_back(1024);
	list2.push_back(2048);
	list2.push_back(3072);
	list2.push_back(4096);

	list.print();
	list2.print();*/
#endif // BASE_CHECK

#ifdef COPY_CHECK
	ForwardList list2 = list;	//Copy constructor
//ForwardList list2;
//list2.push_back(1024);
//list2.push_back(2048);
//list2.push_back(3072);
//list2.push_back(4096);
//list2 = list;	//Copy assignment
	list.print();
	list2.print();
#endif // COPY_CHECK

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	cout << "Список создан, идет загрузка данных" << endl;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "Данные загружены за " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	//list.print();
	cout << delimiter << endl;
	cout << "Копируем список: " << endl;
	t_start = clock();
	ForwardList list2 = list;
	t_end = clock();
	cout << "Список скопирован за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд." << endl;
	//list2.print();  
#endif // PREFORMANCE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	long long arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for: https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	//В данном случае range (диапазон) - это структура данных, для которой должен выполниться 'for'
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef ITERATORS_CHECK
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	ForwardList<int> list1 = { 3, 5, 8, 13, 21 };
	for (int i : list1)cout << i << tab; cout << endl;

	ForwardList<int> list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	//ForwardList list3 = list1 + list2;	//MoveConstructor
	ForwardList<int> list3;
	list3 = list1 + list2;	//MoveAssignment
	for (int i : list3)cout << i << tab; cout << endl;

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list3.insert(value, index);
	for (int i : list3)cout << i << tab; cout << endl;*/

	ForwardList<double> d_list = { 2.5, 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list_1 = { "Хорошо", "живет", "на", "свете" };
	ForwardList<std::string> s_list_2 = { "Винни", "Пух" };
	ForwardList<std::string> s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;
}
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;		//значение элемента
	Element* pNext;	//адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;	//Голова - это указатель на начальный элемент списка,
	//так же как в массиве, имя массива содержит адрес нулевого элмента,
	//Голова списа содержит адрес начального элемента.
public:
	ForwardList()
	{
		Head = nullptr;	//Когда список пуст, его Голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);	//1) Создаем новый элемент
		New->pNext = Head;	//2) Включаем новый элемент в список
		Head = New;		//3) Переносим Голову на новый элемент
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}
	void insert(int Data, int Index)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//3) Включаем созданный элементв список:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//				Removing elements:
	void pop_front()
	{
		Element* Erased = Head;	//1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2) Исключаем удаляемый элемент из списка
		delete Erased;			//3) Удаляем элемент из памяти
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//				Methods:
	void print()const
	{
		/*
		-----------------------
		Для того чтобы перемещаться по списку нужно две вещи:
			1. Итератор;
			2. Цикл;
		-----------------------
		*/
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		cout << number << tab;
		//list.push_front(number);
		list.push_back(number);
	}
	//list.push_back(123);
	list.print();
	//list.pop_back();
	int value;
	int index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	list.insert(value, index);
	list.print();
}
#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
	int capacity;
public:
	virtual void move() = 0;
};

class AirVehicle :public Vehicle
{
	int height;
public:
	virtual void take_off() = 0;
	virtual void land() = 0;
};
class Helicopter :public AirVehicle
{
public:
	void move()
	{
		cout << "������ �� �����" << endl;
	}
	void take_off()
	{
		cout << "�������� � �����" << endl;
	}
	void land()
	{
		cout << "��� ������, ��� � ����" << endl;
	}
};
class AirPlain :public AirVehicle
{
public:
	void take_off()
	{
		cout << "��� ������ ����� ������, � ��� ������� ����� �������� ������" << endl;
	}
	void land()
	{
		cout << "������� ����������� �� ������� ��������, � ������ ���� ����� �������� ������" << endl;
	}
	void move()
	{
		cout << "������ �� ������� ��������" << endl;
	}
};

class GroundVehicle :public Vehicle{};

class Car :public GroundVehicle
{
public:
	void move()
	{
		cout << "������ ���� �� 4� �������" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v;
	//AirVehicle av;
	Helicopter apache;
	apache.take_off();
	apache.move();
	apache.land();

	AirPlain boeing;
	boeing.take_off();
	boeing.move();
	boeing.land();

	//GroundVehicle car;
	Car bmw;
	bmw.move();
}
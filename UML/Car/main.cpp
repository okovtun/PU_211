#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<thread>
using namespace std;

#define Enter	13
#define Escape	27

#define MIN_TANK_VOLUME	28
#define MAX_TANK_VOLUME	80

class Tank
{
	const int VOLUME;
	double fuel_level;
public:
	int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double fuel)
	{
		if (fuel < 0)return;
		fuel_level += fuel;
		if (fuel_level > VOLUME)fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}

	//				Constructors:
	Tank(int volume = 40)
		:VOLUME
		(
			volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
			volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
			volume
		)
	{
		fuel_level = 0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	//			Methos:
	void info()const
	{
		cout << "Volume:  " << VOLUME << " liters.\n";
		cout << "Fuel lvl:" << fuel_level << " liters.\n";
	}
};

#define MIN_ENGINE_CONSUMPTION	4
#define MAX_ENGINE_CONSUMPTION	30

class Engine
{
	double consumption;
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	bool started()const
	{
		return is_started;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	void set_consumption(double consumption)
	{
		if (consumption < MIN_ENGINE_CONSUMPTION)consumption = MIN_ENGINE_CONSUMPTION;
		if (consumption > MAX_ENGINE_CONSUMPTION)consumption = MAX_ENGINE_CONSUMPTION;
		this->consumption = consumption;
		set_consumption_per_second();
	}
	void set_consumption_per_second()
	{
		consumption_per_second = consumption * 3e-5;
	}

	Engine(double consumption)
	{
		set_consumption(consumption);
		//set_consumption_per_second();
		is_started = false;
		cout << "Engine is ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}

	void info()const
	{
		cout << "Consumption per 100 km: " << consumption << " liters.\n";
		cout << "Consumption per second: " << consumption_per_second << " liters.\n";
		cout << "Engine is " << (is_started ? "started" : "stopped") << endl;
	}
};

#define MAX_SPEED_LOW_LIMIT		40
#define MAX_SPEED_HIGH_LIMIT	400
class Car
{
	Engine engine;
	Tank tank;
	int speed;
	const int MAX_SPEED;
	int accelleration;
	bool driver_inside;
	struct Treads
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
	}threads;
public:
	Car(const Engine& engine = 10, const Tank& tank = 60, int max_speed = 250, int accelleration = 10) :
		engine(engine),
		tank(tank),
		speed(0),
		accelleration(accelleration),
		MAX_SPEED
		(
			max_speed<MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed>MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed
		)
	{
		driver_inside = false;
		cout << "Your car is ready to go." << endl;
	}
	Car(int consumption = 10, int volume = 60, int max_speed = 250, int accelleration = 10) :
		engine(consumption),
		tank(volume),
		speed(0),
		accelleration(accelleration),
		MAX_SPEED
		(
			max_speed<MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed>MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed
		)
	{
		driver_inside = false;
		cout << "Your car is redy to go." << endl;
	}
	~Car()
	{
		cout << "Finita la comedia" << endl;
	}
	void fill(double fuel)
	{
		tank.fill(fuel);
	}
	void get_in()
	{
		driver_inside = true;
		//panel();
		threads.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "You are out of your car" << endl;
	}
	void start()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop()
	{
		engine.stop();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();
	}
	void accellerate()
	{
		//if (driver_inside && engine.started())
		speed += accelleration;
		if (speed > MAX_SPEED)speed = MAX_SPEED;
		//if (speed && !threads.free_wheeling_thread.joinable())
		//	threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
		std::this_thread::sleep_for(1s);
	}
	void slow_down()
	{
		//if (driver_inside)
		if (speed)speed -= accelleration * 2;
		if (speed < 0)speed = 0;
		std::this_thread::sleep_for(1s);
	}
	void control()
	{
		cout << "Press Enter to get in" << endl;
		char key = 0;
		do
		{
			if (_kbhit())
			{
				key = _getch();
				switch (key)
				{
				case 'F':case 'f':
					if (driver_inside)
					{
						cout << "�����, �� ����� �����.." << endl;
					}
					else
					{
						double fuel;
						cout << "������� ����� �������: ";
						cin >> fuel;
						tank.fill(fuel);
						//cin.ignore();
						key = 0;
						cout << "���� ������ ����������. Have a nice day :-)" << endl;
					}
					break;
				case 'E':case 'e':case Enter:
					if (speed)
					{
						cout << "\a�_�? ���� ��� ������!!!!" << endl;
						std::this_thread::sleep_for(1s);
						break;
					}
					if (driver_inside)get_out();
					else get_in();
					break;
				case 'I':case 'i':	//Ignition - ���������
					if (driver_inside)engine.started() ? stop() : start();
					break;
				case 'W':case 'w':
					if (driver_inside && engine.started())
					{
						accellerate();
						//std::this_thread::sleep_for(1s);
					}
					break;
				case 'S':case 's':
					if (driver_inside)
					{
						slow_down();
						//std::this_thread::sleep_for(1s);
					}
					break;
				case Escape:
					//if (threads.free_wheeling_thread.joinable())threads.free_wheeling_thread.join();
					if (speed)speed = 0;
					stop();
					get_out();
				}
			}
			if (tank.get_fuel_level() == 0)	stop();
			if (speed && !threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			if (speed == 0 && threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread.join();
		} while (key != Escape);
	}

	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
			std::this_thread::sleep_for(1s);
	}
	void free_wheeling()
	{
		while (speed)
		{
			if (speed-- < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void panel()const
	{
		while (driver_inside)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//�������� ���������� ���� �������
			system("CLS");
			double coeffficient = 2.2;
			for (int i = 0; i < MAX_SPEED / coeffficient; i++)
			{
				SetConsoleTextAttribute(hConsole, 0x02);
				if (i > 110/coeffficient)SetConsoleTextAttribute(hConsole, 0x0E);
				if (i > 200/coeffficient)SetConsoleTextAttribute(hConsole, 0x0C);
				cout << (i < speed / coeffficient ? "|" : ".");
			}
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << endl;
			cout << "Fuel level:\t" << tank.get_fuel_level() << " liters.\t";
			if (tank.get_fuel_level() <= 5)
			{
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Engine is " << (engine.started() ? "started" : "stooped") << endl;
			cout << "Speed:\t" << speed << " km/h.\n";
			std::this_thread::sleep_for(1s);
		}
	}
	void info()const
	{
		cout << "\n=================================\n" << endl;
		engine.info();
		tank.info();
		cout << "Max speed: " << MAX_SPEED << " km/h.\n";
		cout << "\n=================================\n" << endl;
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef TANK_CHECK
	Tank tank;
	double fuel;
	/*do
	{
		cout << "������� ����� �������: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);*/
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	//Car bmw(engine, tank, 280);	bmw.info();
	//Car bmw(Engine(12), Tank(80), 280); bmw.info();

	Car bmw(12, 80, 280, 20);
	/*bmw.fill(25.5);
	bmw.info();*/
	bmw.control();
	}
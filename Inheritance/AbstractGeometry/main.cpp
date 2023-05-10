﻿#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color	//Перечисление - это набор целочисленных констант
	{
		//	  0xAABBGGRR
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
		console_white = 0xFF,
	};
	enum Limitations
	{
		MIN_SIZE = 50,
		MAX_SIZE = 550,
		MIN_START_X = 0,
		MIN_START_Y = 0,
		MAX_START_X = 1000,
		MAX_START_Y = 700,
		MIN_LINE_WIDTH = 3,
		MAX_LINE_WIDTH = 30,
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		void set_start_x(int start_x)
		{
			if (start_x > Limitations::MAX_START_X)start_x = Limitations::MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y > Limitations::MAX_START_Y)start_y = Limitations::MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < Limitations::MIN_LINE_WIDTH)line_width = Limitations::MIN_LINE_WIDTH;
			if (line_width > Limitations::MAX_LINE_WIDTH)line_width = Limitations::MAX_LINE_WIDTH;
			this->line_width = line_width;
			SHRT_MIN;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		void set_side(double side)
		{
			if (side < Dimensions::MIN_SIZE)side = Dimensions::MIN_SIZE;
			if (side > Dimensions::MAX_SIZE)side = Dimensions::MAX_SIZE;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Shape::info();
		}

		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
	};*/

	class Rectangle :public Shape
	{
		double side1, side2;
	public:
		void set_side1(double side1)
		{
			if (side1 < Limitations::MIN_SIZE)side1 = Limitations::MIN_SIZE;
			if (side1 > Limitations::MAX_SIZE)side1 = Limitations::MAX_SIZE;
			this->side1 = side1;
		}
		void set_side2(double side2)
		{
			if (side2 < Limitations::MIN_SIZE)side2 = Limitations::MIN_SIZE;
			if (side2 > Limitations::MAX_SIZE)side2 = Limitations::MAX_SIZE;
			this->side2 = side2;
		}
		double get_side1()const
		{
			return side1;
		}
		double get_side2()const
		{
			return side2;
		}
		double get_area()const override
		{
			return side1 * side2;
		}
		double get_perimeter()const
		{
			return 2 * (side1 + side2);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);	//Контекст устройства окна консоли.
									//Контекст устройства (Device context) - это то, на чем мы рисуем
			//Далее идет то, чем мы рисуем:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//pen - карандаш, рисует контурную линию
			HBRUSH hBrush = CreateSolidBrush(color);	//brush - кисть, рисует заливку

			//Выбираем, чем и на чем будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//Выполняем рисование:
			//::Rectangle(hdc, start_x, start_y, end_x, end_y);
			::Rectangle(hdc, start_x, start_y, start_x + side1, start_y + side2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << side1 << endl;
			cout << "Сторона 2: " << side2 << endl;
			Shape::info();
		}

		Rectangle(double side1, double side2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side1(side1);
			set_side2(side2);
		}
		~Rectangle() {}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		void set_radius(double radius)
		{
			if (radius < Limitations::MIN_SIZE)radius = Limitations::MIN_SIZE;
			if (radius > Limitations::MAX_SIZE)radius = Limitations::MAX_SIZE;
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI*radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius: " << radius << endl;
			Shape::info();
		}

		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
	};
}

void main()
{
	unsigned int number = -1;
	cout << number << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {};
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Square square(5, 100, 500, 25, Geometry::Color::red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(180, 80, 500, 500, 5, Geometry::Color::blue);
	rect.info();

	Geometry::Circle circle(50, 1000, 500, 5, Geometry::Color::yellow);
	circle.info();
}
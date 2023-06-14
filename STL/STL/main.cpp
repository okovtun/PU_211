#include<iostream>
#include<array>
#include<stack>
#include<vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec);

//#define STL_ARRAY
//#define STL_STACK
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	const int N = 5;
	std::array<int, N> arr = { 3,5,8 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_STACK
	std::stack<int> stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	while (!stack.empty())
	{
		cout << stack.top() << endl;
		stack.pop();
	}
#endif // STL_STACK

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамиечского массива;
	//push_back();
	//push_front();
	//insert();
	//erase();
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec.operator[](i) << tab;
	}
	cout << endl;
	vector_properties(vec);
	vec.push_back(55);
	vector_properties(vec);
	vec.reserve(25);	//–езервирует дополнительную вместительность
	//vec.shrink_to_fit();//”резает вместительность до фактического размера вектора
	vec.resize(8);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_properties(vec);
	
	cout << delimiter << endl;
	cout << std::vector<int>().max_size() << endl;
	cout << std::vector<double>().max_size() << endl;
#endif // STL_VECTOR


}

template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;
	cout << "Max size:" << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
}
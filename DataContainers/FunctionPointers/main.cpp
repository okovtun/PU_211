#include<iostream>
using namespace std;

void Hello()
{
	cout << "Hello" << endl;
}
int sum(int a, int b)
{
	return a + b;
}

void main()
{
	void (*p_hello)() = Hello;
	p_hello();

	int (*p_sum)(int, int) = sum;
	cout << (*p_sum)(2, 3) << endl;
}
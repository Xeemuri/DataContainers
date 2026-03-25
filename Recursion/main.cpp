#include <iostream>
using namespace std;

void Elevator(int floor);
int Factorial(int num);
double Power(double a, int n);
int get_fibonacci(int n);
//void Fibonacci(int n);
void Fibonacci(int n, int a = 0, int b = 1);

class Fibonacci
{
	static void Calculate(int n, int a, int b)
	{
		if (a > n) return;
		cout << a << "\t";
		Calculate(n, b, a + b);
	}
public:
	static void Calculate(int n)
	{
		Calculate(n, 0, 1);
		cout << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");

	double a;
	int n;
	//cout << "Введите число: "; cin >> a;
	//cout << "Введите число: "; cin >> n;
	//cout << power(a, n) << endl;
	//cout << factorial(n);
	cout << "Введите предел ряда фибоначчи: "; cin >> n;
	//Fibonacci(n);
	Fibonacci::Calculate(n);
	//Elevator(n);

	main();
}




void Elevator(int floor)
{
	if (floor <= 0)
	{
		cout << "Вы под землей" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	Elevator(floor-1);
	cout << "Вы на " << floor << " этаже" << endl;
}

int Factorial(int num)
{
	return (num == 1) ? 1 : num * Factorial(num - 1);

	/*if (num == 1) return 1;
	else return num * factorial(num -1);*/
}

double Power(double a, int n)
{
	return (n == 0) ? 1 : (n < 0) ? 1 / Power(a, -n) : a * Power(a, n - 1);

	/*if (n == 0) return 1;
	else if (n < 0)
	{
		n = -n;
		return 1 / power(a, n);

		return 1 / a * power(a,n+1);
	}
	else if (n > 0)
	{
		return a * power(a,n-1);
	}*/
}

//void Fibonacci(int n)
//{
//	if (n <= 0) return;
//	static int n1 = 0, n2 = 1; //До меня слишком долго не доходило, что можно так сделать
//	cout << n1 << "\t";
//	int n3 = n1 + n2;
//	n1 = n2;
//	n2 = n3;
//	Fibonacci(n - 1);
//
//	n1 = 0, n2 = 1;
//}

void Fibonacci(int n, int a, int b)
{
	if (a > n) return;
	cout << a << "\t";
	Fibonacci(n, b, a + b);
}

//Я даже до другой реализации догадался
int get_fibonacci(int n)
{
	if (n <= 1) return n;
	else return get_fibonacci(n - 1) + get_fibonacci(n-2);
}

//void Fibonacci(int n)
//{
//	for (int i = 0; i < n; i++) cout << get_fibonacci(i) << "\t";
//}
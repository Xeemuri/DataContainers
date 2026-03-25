#include <iostream>
using namespace std;

void Elevator(int floor);
int factorial(int num);
double power(double a, int n);
int get_fibonacci(int n);
void Fibonacci(int n);

int main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello World!";
	double a;
	int n;
	//cout << "Введите число: "; cin >> a;
	cout << "Введите число: "; cin >> n;
	Fibonacci(n);
	//cout << power(a, n) << endl;
	//Elevator(n);
	//cout << factorial(n);
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

int factorial(int num)
{
	return (num == 1) ? 1 : num * factorial(num - 1);

	/*if (num == 1) return 1;
	else return num * factorial(num -1);*/
}

double power(double a, int n)
{
	return (n == 0) ? 1 : (n < 0) ? 1 / power(a, -n) : a * power(a, n - 1);

	/*if (n == 0) return 1;
	else if (n < 0)
	{
		n = -n;
		return 1 / power(a, n);
	}
	else if (n > 0)
	{
		return a * power(a,n-1);
	}*/
}

void Fibonacci(int n)
{
	if (n <= 0) return;
	static int n1 = 0;
	static int n2 = 1;
	//До меня настолько долго не доходило, что можно их статическими сделать,
	//что я уже до другой реализации догадался
	cout << n1 << "\t";
	int n3 = n1 + n2;
	n1 = n2;
	n2 = n3;
	Fibonacci(n - 1);
	
}

int get_fibonacci(int n)
{
	if (n <= 1) return n;
	else return get_fibonacci(n - 1) + get_fibonacci(n-2);
}

//void Fibonacci(int n)
//{
//	for (int i = 0; i < n; i++) cout << get_fibonacci(i) << "\t";
//}
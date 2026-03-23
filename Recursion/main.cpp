#include <iostream>
using namespace std;

void Elevator(int floor);
int factorial(int num);
double power(double a, int n);
void fibonacci(int n, int n1 = 0, int n2 = 1, bool check = true);

int main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello World!";
	double a;
	int n;
	//cout << "Введите число: "; cin >> a;
	cout << "Введите число: "; cin >> n;
	fibonacci(n, 20, 30);
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

void fibonacci(int n, int n1, int n2,bool check)
{
	if (n1 != 0 || n2 != 1 || check == true)
	{
		n1 = 0;
		n2 = 1;
		check = false;
	}
	else if (check == false)
	{
		if (n == 0) return;
		cout << n1 << endl;
		int n3 = n1 + n2;
		n1 = n2;
		n2 = n3;
		fibonacci(n - 1, n1, n2);
	}
	
}
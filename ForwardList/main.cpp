#include <iostream>
#include <list>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Edestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head; // Голова списка - является точкой входа в список
public:
	ForwardList()
	{
		//Конструктор по умолчанию создает пустой список
		Head = nullptr;
		//Когда список пуст, его Голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "Ldestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		//1) Создаем добавляемый элемент:
		Element* New = new Element(Data);

		//2)Стыкуем новый элемент к началу списка
		New->pNext = Head;

		//3)Смещаем голову на новый элемент
		Head = New;

	}
	void push_back(int Data)
	{
		//1) Создаем добавляемый элемент:
		Element* New = new Element(Data);

		//2) Проверяем есть ли начало в списке
		if (Head == nullptr) Head = New;
		else
		{
			Element* Temp = Head;
			while (Temp->pNext) Temp = Temp->pNext;
			Temp->pNext = New;
		}

	}

	//					Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		Head = Head->pNext;

		//3) Удаляем стираемый элемент из памяти:
		delete Erased;
	}

	void pop_back()
	{
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;

		//2)Удаляем стираемый элемент:
		delete Temp->pNext;

		Temp->pNext = nullptr;
	}

	void insert(int Data, int Index)
	{
		if (Index <= 0) return push_front(Data);
		Element* New = new Element(Data);

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;

	}

	void print() const
	{
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - указатель, при помощи которого можно перемещаться по элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};
void main()
{
	std::list<int> numbers{ 1,2,3 };
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.pop_front();
	//list.pop_back();
	int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value,index);
	list.print();
}
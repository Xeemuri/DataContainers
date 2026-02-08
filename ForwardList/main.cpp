#include <iostream>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
		count++;
	}
	~Element()
	{
		cout << "Edestructor:\t" << this << endl;
		count--;
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head; // Голова списка - является точкой входа в список
	int size;
public:

	//				Constructors, Destructor:
	ForwardList()
	{
		//Конструктор по умолчанию создает пустой список
		Head = nullptr;
		//Когда список пуст, его Голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(int size)
	{
		for (int i = 0; i < size; i++)
		{
			this->push_back(NULL);
		}
	}
	~ForwardList()
	{
		cout << "Ldestructor:\t" << this << endl;
	}

	//				Adding Elements:
	void push_front(int Data)
	{
		//1) Создаем добавляемый элемент:
		Element* New = new Element(Data);

		//2)Стыкуем новый элемент к началу списка
		New->pNext = Head;

		//3)Смещаем голову на новый элемент
		Head = New;
		size++;
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
		size++;
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
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		Head = Head->pNext;

		//3) Удаляем стираемый элемент из памяти:
		delete Erased;
		size--;
	}

	void pop_back()
	{
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;

		//2)Удаляем стираемый элемент:
		delete Temp->pNext;

		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index <= 0) return pop_front();
		
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++)
		{
			if (Temp->pNext->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		Temp->pNext = Temp->pNext->pNext;
	}
	//				Methods:
	void print() const
	{
		Element* Temp = Head; //Temp - это итератор.
		//Итератор - указатель, при помощи которого можно перемещаться по элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	int get_size() const
	{
		Element* Temp = Head;
		int size = 0;
		while (Temp)
		{
			size++;
			Temp = Temp->pNext;
		}
		return size;
	}

	//				Operators override:
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}
};

//#define BASE_CHECK
//#define SIZE_CHECK
#define HOMEWORK1

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
	list.insert(value, index);
	list.erase(0);
	list.print();
#endif // BASE_CHECK

#ifdef SIZE_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);

	list1.print();
	list2.print();
#endif // SIZE_CHECK

#ifdef HOMEWORK1

	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}

	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOMEWORK1

}
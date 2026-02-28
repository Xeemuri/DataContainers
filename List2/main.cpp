#include <iostream>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;//Экземпляры классса можно объявлять непосредственно после описания класса
	//Одним выражением можно объявить несколько переменных одного типа, один раз указав тип данных
	// и перечислив имена объявляемых переменных через запятую.
	size_t size;//size_t - это typedef на 'unsigned int'.

public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" <<this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	~List()
	{
		while (Head) pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding Elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Head = Head->pPrev = new Element(Data,Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index >= size)return;
		if (Index == size-1)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index-1; i++)Temp = Temp->pPrev;
		}
		/*Temp->pPrev->pNext = Temp->pNext->pPrev =
			new Element(Data, Temp->pNext->pNext, Temp->pPrev);*/
		Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		Temp->pPrev = Temp->pPrev->pNext;
		size++;
	}

	//					Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Tail;
			Tail = Head = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void erase(int index)
	{
		if (index >= size)return;
		if (index == size - 1)return pop_back();
		if (index == 0) return pop_front();
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	//					Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for(Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}

};

//#define BASE_CHECK

int main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(value, index);
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK
	List list = { 3,5,8,13 };
	list.print();
}
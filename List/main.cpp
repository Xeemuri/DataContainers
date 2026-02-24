#include <iostream>
#include <ctime>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr):Data(Data),pPrev(pPrev),pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
};
int Element::count = 0;


class List
{
	Element* Head;
	Element* Tail;
	int size;
public:
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int size) :List()
	{
		for (int i = 0; i < size; i++) push_front(0);
		cout << "1argConstructor:\t" << this << endl;
	}
	List(const List& other) : List()
	{

	}
	List(const List&& other) :List()
	{

	}
	~List()
	{
		while (Head != nullptr) pop_front();
		cout << "Ldestructor:\t" << this << endl;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr)
		{
			Head = New;
			Tail = New;
		}
		else
		{
			Tail->pNext = New;
			New->pPrev = Tail;
			Tail = New;
		}
		size++;
	}
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr)
		{
			Head = New;
			Tail = New;
		}
		else
		{
			Head->pPrev = New;
			New->pNext = Head;
			Head = New;
		}
		size++;
	}
	void insert(int Data, int index)
	{
		if (index <= 0) return push_front(Data);
		if (index >= size) return push_back(Data);

		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		New->pPrev = Temp;
		if (Temp->pNext) Temp->pNext->pPrev = New;

		Temp->pNext = New;
		size++;
	}
	void pop_back()
	{
		Element* Erased = Tail;
		Tail = Tail->pPrev;
		if (Tail) Tail->pNext = nullptr;
		else Head = nullptr;
		delete Erased;
		size--;
	}
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		if (Head) Head->pPrev = nullptr;
		else Tail = nullptr;
		delete Erased;
		size--;
	}
	void erase(int index)
	{
		if (index <= 0) return pop_front();
		if (index >= size) return pop_back();

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;

		Temp->pNext = Erased->pNext;

		if(Erased->pNext) Erased->pNext->pPrev = Temp;
		delete Erased;
		size--;
		
	}

	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout <<Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	List& operator= (const List& other)
	{
		if (this == &other) return *this;
			while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}

};


#define BASE_CHECK
//#define HOMEWORK1
//#define COPY_SEMANTIC_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_LIST
//#DEFINE ITERATORS_CHECK
int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list(n);
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
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

#ifdef HOMEWORK1

	ForwardList list(5);
	list.print();
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	list.erase(2);
	list.insert(10, 2);
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOMEWORK1
#ifdef COPY_SEMANTIC_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	ForwardList list2 = list1;
	ForwardList list3 = list1 + list2;
	//list3.print();
	//list1.print();]
	list3.print();
#endif // COPY_SEMANTIC_CHECK
#ifdef MOVE_SEMANTIC_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	ForwardList list3 = list1 + list2;
	list3.print();
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}

	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

#ifdef ITERATORS_CHECK
	ForwardList list1 = { 3,5,8,13,21 };
	ForwardList list2 = { 34,55,89 };
	ForwardList list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK
	return 0;
}


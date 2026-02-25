#include <iostream>
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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class List;
	friend class Iterator;
	friend class ConstIterator;
	friend List operator+ (const List& left, const List& right);
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};
class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ConstIterator operator++(int)
	{
		ConstIterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const ConstIterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other) const
	{
		return this->Temp != other.Temp;
	}
	int operator*() const
	{
		return Temp->Data;
	}
};


class List
{
	Element* Head;
	Element* Tail;
	int size;
public:
	ConstIterator begin() const
	{
		return Head;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	int get_size() const
	{
		return size;
	}
	Element* get_head()const
	{
		return Head;
	}
	Element* get_tail()const
	{
		return Tail;
	}
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
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
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

	int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}
};

List operator+ (const List& left, const List& right)
{
	List result = left;
	for (ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		result.push_back(*it);
	}
	return result;
}


//#define BASE_CHECK
//#define HOMEWORK1
//#define COPY_SEMANTIC_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_LIST
#define ITERATORS_CHECK
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

	List list(5);
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
	List list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	//list1 = list1;
	//list1.print();

	List list3 = list1;
	//list3.print();
	//list1.print();]
	list3.print();
#endif // COPY_SEMANTIC_CHECK
#ifdef MOVE_SEMANTIC_CHECK
	List list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	List list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	List list3 = list1 + list2;
	list3.print();
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_LIST
	List list = { 3,5,8,13,21 };
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
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK
	return 0;
}


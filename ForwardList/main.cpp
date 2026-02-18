#include <iostream>
#include <ctime>
#include <vector>
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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		count++;
	}
	~Element()
	{
#ifdef DEBUG
		cout << "Edestructor:\t" << this << endl;
#endif // DEBUG

		count--;
	}
	friend class ForwardList;
	friend class Iterator;
	friend ForwardList operator+ (const ForwardList& left, const ForwardList& right);
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
		/*Iterator old = *this;
		if (Temp) Temp = Temp->pNext;
		return old;*/
		Temp = Temp->pNext;
		return *this;
	}
	bool operator!=(const Iterator& other)
	{
		 return this->Temp == other.Temp ? false : true;
	}
	int operator*() const
	{
		return Temp->Data;
	}
	operator int()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head; // Голова списка - является точкой входа в список
	int size;
public:

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	//				Constructors, Destructor:
	ForwardList()
	{
		//Конструктор по умолчанию создает пустой список
		Head = nullptr;
		//Когда список пуст, его Голова указывает на 0.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size) : ForwardList()
	{
		for (int i = 0; i < size; i++)
		{
			this->push_front(0);
		}
		cout << "1argConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int> &il) :ForwardList()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//Deep copy
		*this = other;
		reverse();
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		//Shallow copy
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "Ldestructor:\t" << this << endl;
	}

	//				Adding Elements:
	void push_front(int Data)
	{
		//1) Создаем добавляемый элемент:
		//Element* New = new Element(Data);

		//2)Стыкуем новый элемент к началу списка
		//New->pNext = Head;

		//3)Смещаем голову на новый элемент
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем добавляемый элемент:
		//Element* New = new Element(Data);

		//2) Проверяем есть ли начало в списке

		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index <= 0) return push_front(Data);
		//Element* New = new Element(Data);

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);
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
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}
	//				Methods:

	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print() const
	{
		//Element* Temp = Head; //Temp - это итератор.
		////Итератор - указатель, при помощи которого можно перемещаться по элементам структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	Element* get_head()const
	{
		return Head;
	}
	int get_size() const
	{
		return size;
	}

	//				Operators override:

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	//ForwardList operator+(const ForwardList& other) const
	//{
	//	ForwardList newList;// = new ForwardList();
	//	/*Element* Temp = this->Head;*/
	//	for (Element* Temp = this->Head; Temp; Temp = Temp->pNext)
	//		newList.push_back(Temp->Data);

	//	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
	//		newList.push_back(Temp->Data);
	//	return newList;
	//}
};

ForwardList operator+ (const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	for (Element* Temp = right.get_head(); Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);
	return result;
}

//#define BASE_CHECK
//#define SIZE_CHECK
//#define HOMEWORK1
//#define COPY_SEMANTIC_CHECK
//#define PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY

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
#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list1;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		list1.push_back(rand() % 100);
	}
	clock_t end = clock();
	cout << delimeter << endl;
	cout << "list1 заполнен за " << double(end - start) / CLOCKS_PER_SEC << endl;
	list1.print();
	cout << delimeter << endl;
	start = clock();
	ForwardList list2 = list1;
	end = clock();
	cout << delimeter << endl;
	cout << "list2 скопирован за " << double(end - start) / CLOCKS_PER_SEC << endl;
	list2.print();
	cout << delimeter << endl;
#endif // PERFORMANCE_CHECK

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
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	//ForwardList list = {3, 5,8};
	//list.print();

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}

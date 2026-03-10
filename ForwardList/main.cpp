#include <iostream>
#include <ctime>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"

template<typename T> class ForwardList;
template<typename T> class Iterator;
template<typename T> class ConstIterator;

template<typename T> class Element
{
	T Data;
	Element<T>* pNext;
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend class ConstIterator<T>;
	friend ForwardList<T> operator+ (const ForwardList<T>& left, const ForwardList<T>& right);
};
template<typename T> int Element<T>::count = 0;

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
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
		Iterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator<T>& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other) const
	{
		return this->Temp != other.Temp;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};
template<typename T> class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ConstIterator<T> operator++(int)
	{
		ConstIterator<T> old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const ConstIterator<T>& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator<T>& other) const
	{
		return this->Temp != other.Temp;
	}
	T operator*() const
	{
		return Temp->Data;
	}
};

template<typename T> class ForwardList
{
	Element<T>* Head; // Голова списка - является точкой входа в список
	int size;
public:

	Element<T>* get_head()const;
	int get_size() const;

	ConstIterator<T> begin() const;
	ConstIterator<T> end() const;
	Iterator<T> begin();
	Iterator<T> end();

	//				Constructors, Destructor:
	ForwardList();
	explicit ForwardList(int size);
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other);

	~ForwardList();

	//				Operators override:

	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);
	T& operator[](int index)const;

	//				Adding Elements:

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//				Removing elements:

	void pop_front();
	void pop_back();
	void erase(int Index);

	//				Methods:

	void reverse();
	void print() const;
};
template <typename T> Element<T>* ForwardList<T>::get_head()const
{
	return Head;
}
template <typename T> int ForwardList<T>::get_size() const
{
	return size;
}

template <typename T> ConstIterator<T> ForwardList<T>::begin() const
{
	return Head;
}
template <typename T>ConstIterator<T> ForwardList<T>::end() const
{
	return nullptr;
}
template <typename T> Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template <typename T> Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}

//				Constructors, Destructor:
template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(int size) : ForwardList()
{
	for (int i = 0; i < size; i++)
	{
		this->push_front(0);
	}
	cout << "1argConstructor:\t" << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T> ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	//Deep copy
	*this = other;
	reverse();
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(ForwardList<T>&& other) :ForwardList()
{
	//Shallow copy
	*this = std::move(other);
	cout << "LMoveConstructor:\t" << this << endl;
}

template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "Ldestructor:\t" << this << endl;
}

//				Adding Elements:
template<typename T> void ForwardList<T>::push_front(T Data)
{
	Head = new Element<T>(Data, Head);
	size++;
}

template<typename T> void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);

	Element<T>* Temp = Head;
	while (Temp->pNext) Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data);
	size++;
}

template<typename T> void ForwardList<T>::insert(T Data, int Index)
{
	if (Index <= 0) return push_front(Data);

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		if (Temp->pNext == nullptr) break;
		Temp = Temp->pNext;
	}

	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}

//				Removing elements:
template<typename T>void ForwardList<T>::pop_front()
{
	//1) Запоминаем адрес удаляемого элемента
	Element<T>* Erased = Head;
	Head = Head->pNext;

	//3) Удаляем стираемый элемент из памяти:
	delete Erased;
	size--;
}

template<typename T>void ForwardList<T>::pop_back()
{
	//1) Доходим до конца списка:
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext) Temp = Temp->pNext;

	//2)Удаляем стираемый элемент:
	delete Temp->pNext;

	Temp->pNext = nullptr;
	size--;
}

template<typename T>void ForwardList<T>::erase(int Index)
{
	if (Index <= 0) return pop_front();

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		if (Temp->pNext->pNext == nullptr) break;
		Temp = Temp->pNext;
	}
	Element<T>* Erased = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete Erased;
	size--;
}
//				Methods:

template<typename T>void ForwardList<T>::reverse()
{
	ForwardList<T> reverse;
	while (Head)
	{
		reverse.push_front(Head->Data);
		pop_front();
	}
	this->Head = reverse.Head;
	reverse.Head = nullptr;
}
template<typename T>void ForwardList<T>::print() const
{
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке: " << size << endl;
	cout << "Общее количество элементов: " << Element<T>::count << endl;
}

//				Operators override:

template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other) return *this;
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)
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

template<typename T> T& ForwardList<T>::operator[](int index)const
{
	Element<T>* Temp = Head;
	for (int i = 0; i < index; i++) Temp = Temp->pNext;
	return Temp->Data;
}

template<typename T> ForwardList<T> operator+ (const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> result = left;
	for (ConstIterator<T> it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		result.push_back(*it);
	}
	return result;
}

#define BASE_CHECK
//#define SIZE_CHECK
//#define HOMEWORK1
//#define COPY_SEMANTIC_CHECK
//#define PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define ITERATORS_CHECK
int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//int n;
	//cout << "Введите размер списка: "; cin >> n;
	//ForwardList<int> list(n);
	//for (int i = 0; i < n; i++)
	//{
	//	list.push_front(rand() % 100);
	//}
	//list.print();
	////list.pop_front();
	////list.pop_back();
	//int index, value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(value, index);
	//list.erase(0);
	//list.print();
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
	ForwardList<int> list1 = { 3,5,8,13,21 };
	ForwardList<int> list2 = { 34,55,89 };
	ForwardList<int> list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
	cout << delimeter << endl;

	//TODO: need check on diff types

	ForwardList<double> d_list_1 = { 2.7, 3.14, 1.8, 5.2 };
	ForwardList<double> d_list_2 = { 8.33, 9.11, 7.55 };
	ForwardList<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	for (double i : d_list_3)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list_1 = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	ForwardList<std::string> s_list_2 = { "и","Пяточек","тоже" };
	ForwardList<std::string> s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_1)cout << i << tab; cout << endl;
	for (std::string i : s_list_2)cout << i << tab; cout << endl;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK
	return 0;
}
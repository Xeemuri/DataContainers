#include <iostream>
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"
/////////////////////////////////////////////////////////////////////////////////////
/////////////		Class declaration (Объявление класса)				/////////////
template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	} *Head, *Tail;//Экземпляры классса можно объявлять непосредственно после описания класса
	//Одним выражением можно объявить несколько переменных одного типа, один раз указав тип данных
	// и перечислив имена объявляемых переменных через запятую.

	size_t size;//size_t - это typedef на 'unsigned int'.

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*()const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator* ();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		T& operator* ();
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	List();
	List(const std::initializer_list<T>& il);
	List(const std::initializer_list<const char*> il);
	~List();

	//					Adding Elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing Elements:
	void pop_front();
	void pop_back();
	void erase(int index);
	//					Methods:
	void print()const;
	void reverse_print()const;

};
/////////////		Class declaration end (Объявление класса)			/////////////
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
/////////////		Class definition (Определение класса)				/////////////

//---------------------------------------------------------------------------------//
//---------				Element methods								---------------//
template<typename T>List<T>::Element::Element(T Data, Element * pNext, Element * pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
//---------				Element methods end							---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------					ConstBaseIterator methods				
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
//---------					ConstBaseIterator methods				---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------					ConstIterator methods					---------------//
template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstIterator::~ConstIterator() {}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>  typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//---------					ConstIterator methods end				---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------				ConstReverseIterator methods				---------------//
template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator() {}

template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
//---------			ConstReverseIterator methods end				---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------					Iterator methods						---------------//
template<typename T> List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}
template<typename T> List<T>::Iterator::~Iterator() {}
template<typename T> T& List<T>::Iterator::operator* ()
{
	return ConstBaseIterator::Temp->Data;
}
//---------					Iterator methods end					---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------				ReverseIterator methods						---------------//
template<typename T> List<T>::ReverseIterator::ReverseIterator(Element * Temp) : ConstReverseIterator(Temp) {}
template<typename T> List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T> T& List<T>::ReverseIterator::operator* ()
{
	return ConstBaseIterator::Temp->Data;
}
//---------				ReverseIterator methods						---------------//
//---------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------//
//---------				List methods								---------------//
template<typename T> typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}
template<typename T> List<T>::List(const std::initializer_list<const char*> il) :List()
{
	for (const char* const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(const_cast<char*> (*it));
	}
}
template<typename T> List<T>::~List()
{
	while (Head) pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//					Adding Elements:
template<typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	if (Index >= size)return;
	if (Index == size - 1)return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	/*Temp->pPrev->pNext = Temp->pNext->pPrev =
		new Element(Data, Temp->pNext->pNext, Temp->pPrev);*/
	Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	Temp->pPrev = Temp->pPrev->pNext;
	size++;
}

//					Removing Elements:
template<typename T>void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
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
template<typename T> void List<T>::erase(int index)
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
template<typename T> void List<T>::print()const
{
	cout << "Head:\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов в списке: " << size << endl;
}
template<typename T> void List<T>::reverse_print()const
{
	cout << "Tail:\t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head:\t" << Head << endl;
	cout << "Количество элементов в списке: " << size << endl;
}
//---------				List methods end							---------------//
//---------------------------------------------------------------------------------//

/////////////		Class definition end (Конец определения класса)		/////////////
/////////////////////////////////////////////////////////////////////////////////////
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

	List<int> iList = { 3,5,8,13,21 };
	for (int i : iList) cout << i << tab; cout << endl;
	for (List<int>::ReverseIterator it = iList.rbegin(); it != iList.rend(); ++it)
		cout << *it << tab; cout << endl;

	List<double> dList = { 3.5, 21.4, 41.2, 67.69, 0.22 };
	for (double i : dList) cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = dList.rbegin(); it != dList.rend(); ++it)
		cout << *it << tab; cout << endl;

	List<char> cList = { 'a','b','c','d','z' };
	for (char i : cList) cout << i << tab;
	cout << endl;

	List<std::string> sList = { "Хорошо","живет", "на", "свете", "Винни", "Пух"};
	for (std::string i : sList)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = sList.rbegin(); it != sList.rend(); ++it)
		cout << *it << tab; cout << endl;
	//for (List<int>::Iterator it = list.begin(); it != list.end(); it++)
	//{
	//	*it *= 100;
	//	cout << *it << tab;
	//}
	//cout << endl;

	//for (List<int>::ConstReverseIterator it = list.rbegin(); it != list.rend(); it++)
	//{
	//	cout << *it << tab;
	//}

}
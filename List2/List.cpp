#include "List.h"
/////////////////////////////////////////////////////////////////////////////////////
/////////////		Class definition (Определение класса)				/////////////

//---------				Element methods								---------------//
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
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

//								ConstIterators:

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



//								Iterators:
template<typename T> T& List<T>::Iterator::operator* ()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T> T& List<T>::ReverseIterator::operator* ()
{
	return ConstBaseIterator::Temp->Data;
}


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

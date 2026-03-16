#pragma once
#include <iostream>
using std::cout;
using namespace std;

#define tab '\t'
#define delimeter "\n-----------------------\n"
/////////////////////////////////////////////////////////////////////////////////////
/////////////		Class declaration (Объявление класса)				/////////////
template<typename T> class ForwardList;
template<typename T> class Iterator;
template<typename T> class ConstIterator;
template<typename T> ForwardList<T> operator+ (const ForwardList<T>& left, const ForwardList<T>& right);

template<typename T> class Element
{
	T Data;
	Element<T>* pNext;
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
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
	Iterator(Element<T>* Temp = nullptr);
	~Iterator();
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator<T>& other) const;
	bool operator!=(const Iterator<T>& other) const;
	T& operator*();
};
template<typename T> class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp = nullptr);
	~ConstIterator();
	ConstIterator<T>& operator++();
	ConstIterator<T> operator++(int);
	bool operator==(const ConstIterator<T>& other) const;
	bool operator!=(const ConstIterator<T>& other) const;
	T operator*() const;
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
/////////////		Class declaration end (Объявление класса)			/////////////
/////////////////////////////////////////////////////////////////////////////////////

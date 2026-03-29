#include <iostream>
#include<cmath>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------\n"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;

public:
	Tree() :Root(nullptr)
	{
		//cout << "TConstructor:\t" << this << endl;
	}
	Tree(int Root_data)
	{
		Root = new Element(Root_data);
		//cout << "1ArgConstructor:\t" << this << endl;
	}
	~Tree()
	{
		//cout << "TDestructor:\t" << this << endl;
	}
	Element* get_Root() const
	{
		return Root;
	}
	int count(Element* Root) const
	{

	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}

		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void print(Element* Root)
	{
		if (Root)
		{
			cout << Root->Data;
			if (Root->Data == this->Root->Data) cout << " - Корень ";
			cout << endl;
			print(Root->pLeft);
			print(Root->pRight);
		}
	}
	void print1(Element* Root)
	{
		if (Root)
		{
			print1(Root->pLeft);
			print1(Root->pRight);
			cout << Root->Data;
			if (Root->Data == this->Root->Data) cout << " - Корень ";
			cout << endl;
		}
	}
	void print2(Element* Root)
	{
		if (Root)
		{
			print2(Root->pLeft);
			cout << Root->Data;
			if (Root->Data == this->Root->Data) cout << " - Корень ";
			cout << endl;
			print2(Root->pRight);
		}
	}
};


int main()
{
	setlocale(LC_ALL, "RUS");
	Tree tree(10);
	tree.insert(2, tree.get_Root());
	tree.insert(1, tree.get_Root());
	tree.insert(4, tree.get_Root());
	tree.insert(13, tree.get_Root());
	tree.insert(9, tree.get_Root());
	tree.insert(20, tree.get_Root());
	tree.print1(tree.get_Root());
}
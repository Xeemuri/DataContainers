#include <iostream>
#include<cmath>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------\n"

class Tree
{
	class Element
	{
		static int sum;
		static int count;
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
			count++;
			sum += Data;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
			count--;
			sum -= Data;
		}
		int get_count() const
		{
			return count;
		}
		int get_sum() const
		{
			return sum;
		}
		friend class Tree;
	}*Root;

public:
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(int Root_data)
	{
		Root = new Element(Root_data);
		cout << "1ArgConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	Element* getRoot() const
	{
		return Root;
	}

	int sum(Element* Root) const
	{
		return !Root ? 0: sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
		//if (!Root) return 0;
		//else return sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	int count(Element* Root) const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	double avg() const
	{
		return (double)sum(getRoot()) / count(getRoot());
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;

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

	void print(Element* Root) const
	{
		if (Root == nullptr)return;

		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	
	int minValue(Element* Root) const
	{
		if (!this->Root) return 0;
		return !Root->pLeft ? Root->Data : minValue(Root->pLeft);
		//if (!Root->pLeft)return Root->Data;
		//else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (!this->Root) return 0;
		return !Root->pRight ? Root->Data : maxValue(Root->pRight);
		//if (!Root->pRight)return Root->Data;
		//else return maxValue(Root->pRight);
	}
};
int Tree::Element::sum = 0;
int Tree::Element::count = 0;

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	Tree tree;
	cout << "Введите размер дерева: "; cin >> n;

	for (int i = 0; i < n; i++)
	{
		tree.insert(-rand() % 20, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.sum(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree.count(tree.getRoot()) << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree.avg() << endl;
}	
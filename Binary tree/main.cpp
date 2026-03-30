#include <iostream>
#include<cmath>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------\n"

class Tree
{
protected:
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
		friend class UniqueTree;
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

	double avg() const
	{
		return (double)sum(getRoot()) / count(getRoot());
	}

	void insert(int Data)
	{
		return insert(Data, Root);
	}
	int minValue() const
	{
		return minValue(Root);
	}
	int maxValue() const
	{
		return maxValue(Root);
	}
	void print() const
	{
		return print(Root);
	}
	int sum() const
	{
		return sum(Root);
	}
	int count() const
	{
		return count(Root);
	}

private:
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

	int minValue(Element* Root) const
	{
		if (!this->Root) return 0;
		else return !Root->pLeft ? Root->Data : minValue(Root->pLeft);
	}

	void print(Element* Root) const
	{
		if (Root == nullptr)return;

		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	int maxValue(Element* Root)const
	{
		if (!this->Root) return 0;
		else return !Root->pRight ? Root->Data : maxValue(Root->pRight);

	}

	int sum(Element* Root) const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	int count(Element* Root) const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
};
int Tree::Element::sum = 0;
int Tree::Element::count = 0;


class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;

		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		return insert(Data, Root);
	}
};
int main()
{
	setlocale(LC_ALL, "RUS");
	int n;

	Tree tree;

	cout << "Введите размер дерева: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100 - 50);
	}
	tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " <<			tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " <<			tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " <<					tree.sum() << endl;
	cout << "Количество элементов дерева: " <<				tree.count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " <<	tree.avg() << endl;


	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " <<			u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " <<			u_tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " <<					u_tree.sum() << endl;
	cout << "Количество элементов дерева: " <<				u_tree.count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " <<	u_tree.avg() << endl;
}
#include <iostream>
#include <ctime>
using namespace std;

#define tab "\t"
#define delimiter "\n--------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;


public:
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it);
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
		print(Root);
		cout << endl;
	}
	int sum() const
	{
		return sum(Root);
	}
	int count() const
	{
		return count(Root);
	}
	int depth() const
	{
		return depth(Root);
	}
	void clear()
	{
		clear(Root);
		//Root = nullptr;
	}
	void erase(int Data)
	{
		//Root = erase(Data, Root);
		erase(Data, Root);
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

	int depth(Element* Root) const
	{
		if (Root == nullptr) return 0;
		if (depth(Root->pLeft) > depth(Root->pRight))return depth(Root->pLeft) + 1;
		else return depth(Root->pRight) + 1;
	}

	void clear(Element*& Root)
	{
		if (!Root) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}

	//Element* erase(int Data, Element*& Root)
	//{
	//	if (!Root)return nullptr;
	//	if (Root->Data == Data)
	//	{
	//		if (!Root->pLeft && !Root->pRight)
	//		{
	//			delete Root;
	//			Root = nullptr;
	//		}
	//		else if (!Root->pLeft ||!Root->pRight)
	//		{
	//			Element* child = (Root->pLeft) ? Root->pLeft : Root->pRight;
	//			delete Root;
	//			return child;
	//		}
	//		else
	//		{
	//			if (count(Root->pLeft) > count(Root->pRight))
	//			{
	//				int maxVal = maxValue(Root->pLeft);
	//				Root->Data = maxVal;
	//				erase(maxVal, Root->pLeft);
	//			}
	//			else
	//			{
	//				int minVal = minValue(Root->pRight);
	//				Root->Data = minVal;
	//				erase(minVal, Root->pRight);
	//			}
	//		}
	//	return Root;
	//	}
	//	if (Data < Root->Data) Root->pLeft = erase(Data, Root->pLeft);
	//	if (Data > Root->Data) Root->pRight = erase(Data, Root->pRight);
	//	return Root;
	//}

	void erase(int Data, Element*& Root)
	{
		if (!Root)return;
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
		if (Root)
		{
			if (Root->pLeft)erase(Data, Root->pLeft);
			if (Root->pRight)erase(Data, Root->pRight);
		}
	}
};


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

//#define BASE_CHECK

int main()
{
	setlocale(0, "");

#ifdef BASE_CHECK
	int n;

	Tree tree;

	cout << "Введите размер дерева: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100 - 50);
	}
	tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Количество элементов дерева: " << tree.count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree.avg() << endl;


	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Количество элементов дерева: " << u_tree.count() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << u_tree.avg() << endl;
#endif // BASE_CHECK
	Tree tree = { 50, 25, 75, 75, 16, 32, 64, 85, 91, 95};
	tree.print();
	int n;
	cout << "Глубина дерева: " << tree.depth() << endl;
	cout << "Введите удаляемое значение: ";cin >> n;
	tree.erase(n);
	//tree.clear();
	tree.print();
}
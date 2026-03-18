#include "List.cpp"
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

	List<std::string> sList = { "Хорошо","живет", "на", "свете", "Винни", "Пух" };
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
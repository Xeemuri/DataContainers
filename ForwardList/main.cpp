#include"ForwardList.h";
#include"ForwardList.cpp"
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


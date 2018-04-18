// DemonList_Finaly.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Chain
{
	string stroka;
	Chain *next, *prev;
};

class List
{
	Chain *Head, *Tail;
public:
	List() 
	{
		Head = NULL;
		Tail = NULL;
	}; //Инициализируем адреса как пустые

	~List()
	{
		while (Head) //Пока по адресу на начало списка что-то есть
		{
			Tail = Head->next; //Резервная копия адреса следующего звена списка
			delete Head; //Очистка памяти от первого звена
			Head = Tail; //Смена адреса начала на адрес следующего элемента
		}
	}

	void Show(int a)
	{
		Chain *temp;
		if (a == 2)
		{
			//ВЫВОДИМ СПИСОК С КОНЦА
			temp = Tail; //Временный указатель на адрес последнего элемента
			while (temp != NULL) //Пока не встретится пустое значение
			{
				cout << temp->stroka << " -> "; //Выводить значение на экран
				temp = temp->prev; //Указываем, что нужен адрес предыдущего элемента
			}
			cout<< "NULL" << "\n";
		}

		if (a == 1)
		{
			//ВЫВОДИМ СПИСОК С НАЧАЛА
			temp = Head; //Временно указываем на адрес первого элемента
			while (temp != NULL) //Пока не встретим пустое значение
			{
				cout << temp->stroka << " -> "; //Выводим каждое считанное значение на экран
				temp = temp->next; //Смена адреса на адрес следующего элемента
			}
			cout<< "NULL" << "\n";
		}
	}

	void Delete_First_Last(int a)
	{
		Chain *temp;
		if (a == 1)
		{
			if (Head)
			{
				temp = Head;
				Head = Head->next;
				delete temp;
				if (Head == NULL) 
					Tail = Head;
				else 
					Head->prev = NULL;
			}
		}

		if (a == 2)
		{
			if (Tail)
			{
				temp = Tail;
				Tail = Tail->prev;
				delete temp;
				if (Tail == NULL)
					Head = Tail;
				else 
					Tail->next = NULL;
			}
		}
	}
	
	void Delete(Chain *del)
	{
		Chain *tempBefore = del->prev;
		Chain *tempAfter = del->next;
		tempBefore->next = tempAfter;
		tempAfter->prev = tempBefore;
		delete del;
	}

	void Add(int a)
	{
		string x;
		cout << "Введите новый элемент списка: ";
		cin >> x;
		Chain *temp = new Chain; //Выделение памяти под новый элемент структуры
		if (a == 1) //В НАЧАЛО списка
		{
			temp->next = Head;
			if (Head) //Если список не пуст
			{
				temp = Head;                 // Пояснения в другом if
				Head->prev = new Chain;
				Head = Head->prev;
				Head->stroka = x;
				Head->next = temp;
				Tail->prev = NULL;
			}
			else //Если список пустой
			{
				temp->stroka = x;
				temp->prev = NULL; //Предыдущий элемент указывает в пустоту
				temp->next = NULL; 
				Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
			}
		}

		if (a == 2) //В КОНЕЦ списка
		{
			if (Head) //Если список не пуст
			{
				//cout<<"1"<<endl;
				temp = Tail;//Резервная копия хвоста
				Tail->next = new Chain;//Там, где был указатель на NULL теперь будет указатель на какой-то элем.
				Tail = Tail->next;//Теперь хвост - это тот элем., что в верхней строке
				Tail->stroka = x;//Записываем в новый хвост строку которую мы ввели
				Tail->next = NULL;//Последние штрихи
				Tail->prev = temp;
			}
			else //Если список пустой
			{
				//cout<<"2"<<endl;
				temp->stroka = x;
				temp->prev = NULL; //Предыдущий элемент указывает в пустоту
				temp->next = NULL; 
				Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
			}
		}
	}
	
	void Add_after(Chain *afterWord)
	{
		string x;
		cout << "Введите новый элемент списка: ";
		cin >> x;
		Chain *temp = new Chain; //Выделение памяти под новый элемент структуры
		temp->next = afterWord->next;
		temp->prev = afterWord;
		afterWord->next = temp;
		temp->stroka = x;
		temp = temp->next;
		temp->prev = afterWord->next;
	}

	struct Chain *Search(string text)
	{
		Chain *temp = Head;
		while (temp)
		{
			if (text == temp->stroka) 
				return temp;
			else
				temp = temp->next;
		}
		return NULL;
	}

	void StreamInput()
	{
		string x;
		string word;
		cout << "Введите строку с точкой в конце (желательно английскими буквами, иначе - последствия непредсказуемы): ";
		getline(cin, x);
		while (!(x.length()) || x[x.length()-1]!='.' || x.length()<2)
		{
			cout << "Строка пуста или отсутствует точка в конце строки! Повторите ввод!\n";
			getline(cin, x);
		}
		Chain *temp = new Chain;
		for (int i = 0; i < x.length(); i++)
		{
			if (isalpha(x[i]))
			{
				word = word + x[i];
			}
			else
			{
				if ((x[i] == ' ' && x[i-1] == ' ') || word == "") //Пропуск пробелов и средство против: .......
					continue;
				if (Head) //Если список не пуст
				{
					//cout<<"1"<<endl;
					temp = Tail;
					Tail->next = new Chain;
					Tail = Tail->next;
					Tail->stroka = word;
					Tail->next = NULL;
					Tail->prev = temp;
				}
				else //Если список пустой
				{
					//cout<<"2"<<endl;
					temp->stroka = word;
					temp->prev = NULL; //Предыдущий элемент указывает в пустоту
					temp->next = NULL; 
					Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
				}
				word = "";
			}
		}
		//Костыль для удаления пустых элем. в начале и в конце списка (появляются если стрим инпуте ввести сначала пробел а потом слово
		//или поставить перед точкой пару пробелов)
		if(Head)
		{
			if (Head->stroka == "")
			{
				temp = Head;
				Head = Head->next;
				delete temp;
				if (Head == NULL) 
					Tail = Head;
				else 
					Head->prev = NULL;
			}
			if (Tail->stroka == "")
			{
				temp = Tail;
				Tail = Tail->prev;
				delete temp;
				if (Tail == NULL)
					Head = Tail;
				else 
					Tail->next = NULL;
			}
		}
	}

	void Special_first()
	{
		Chain *temp = Head->next;
		bool goodCheck = false;
		bool goodWord = true;
		string alfa = "abcdefghijklmnopqrstuvwxyz";
		cout <<"Ваши слова:\n";
		while (temp) //Пока не встретится пустое значение
		{
			goodCheck = false;
			goodWord = true;
			if (Head->stroka.length() != temp->stroka.length())
				goodCheck = true;
			else
			{
				for (int i = 0; i<temp->stroka.length(); i++)
				{
					if (temp->stroka[i] != Head->stroka[i])
					{
						goodCheck = true;
						i = temp->stroka.length();
					}
				}
			}
			if (goodCheck)
			{
				for (int j = 0; j<temp->stroka.length(); j++)
				{
					if (temp->stroka[j] != alfa[j])
					{
						goodWord = false;
						j = temp->stroka.length();
					}
				}
				if (goodWord)
				{
					cout << temp->stroka << endl;
				}
			}
			temp = temp->next; //Указываем, что нужен адрес следующего элемента
		}
	}

	void Special_second()
	{
		Chain *temp = Head->next;
		bool goodCheck = false;
		bool goodWord = true;
		string alfa = "abcdefghijklmnopqrstuvwxyz";
		cout <<"Ваши слова:\n";
		while (temp) //Пока не встретится пустое значение
		{
			goodCheck = false;
			goodWord = true;
			if (Head->stroka.length() != temp->stroka.length())
				goodCheck = true;
			else
			{
				for (int i = 0; i<temp->stroka.length(); i++)
				{
					if (temp->stroka[i] != Head->stroka[i])
					{
						goodCheck = true;
						i = temp->stroka.length();
					}
				}
			}
			if (goodCheck)
			{
				for (int j = 0; j<temp->stroka.length(); j++)
				{
					if (temp->stroka[j] != alfa[j])
					{
						goodWord = false;
						j = temp->stroka.length();
					}
				}
				if (goodWord)
				{
					temp->stroka.erase(temp->stroka.begin());
					temp->stroka += ".";
					cout << temp->stroka << endl;
				}
			}
			temp = temp->next; //Указываем, что нужен адрес следующего элемента
		}
	}
};

int main()
{
	bool work = true;
	setlocale(LC_ALL, "rus");
	List MyList;
	MyList.StreamInput();
	char c;
	while (work)
	{
		system("cls");
		cout << "Выберите что вам нужно:" << endl
			<< "1. Найти элемент в списке" << endl
			<< "2. Добавить элемент в список" << endl
			<< "3. Вывести список в консоль" << endl //ТОМУ КТО ЧИТАЕТ МОЙ КОД: Если ты вдруг пытаешся понять как тут все работает советую начать с Show
			<< "4. Удалить элемент списка" << endl
			<< "5. Удалить список" << endl
			<< "6. Напечатать все слова, которые отличаются от первого и совпадают с началом алфавита (a, ab, abc, ...)" << endl
			<< "7. Удалить первую букву в этих словах и каждому слову дописать точку" << endl
			<< "8. Дописать строку в конец списка (или заполнить заново если список пуст)" << endl
			<< "9. Закончить работу\n--------------------------------------------------------------------------------------------------------" << endl;
			cout <<"Список до изменений: "; MyList.Show(1);
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
		c = _getch();
		switch (c)
		{
			case '1':
			{
				cout << "Введите слово, которое будем искать: ";
				string find_it;
				cin >> find_it;
				Chain *element = new Chain;
				element = MyList.Search(find_it);
				if (!(element))
				{
					cout<<"Такого элемента нет в списке, проверьте корректность ввода\n";
					_getch();
					break;
				}
				cout <<"Ваш элемент находится между элементами, которые находятся в "<< element->prev <<" и "<<element->next<<" ячейках памяти"<<endl;
				_getch();
				break;
			}
			case '2':
			{
				int a;
				cout << "1. Добавить элемент в начало списка\n2. Добавить элемент в конец списка\n3. Добавить элемент после какого-то элемента в СЕРЕДИНЕ списка\n";
				while (!(cin >> a) || a<1 || a>3)
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Некорректный ввод! Повторите!\n";
				}
				if (a==1 || a==2)
					MyList.Add(a);
				else
				{
					cout << "Введите слово, после которого хотите вставить новый элемент: ";
					string after;
					cin >> after;
					while (!(after.length()))
					{
						cout << "Строка пуста! Повторите ввод!\n";
						cin>>after;
					}
					Chain *element = new Chain;
					element = MyList.Search(after);
					if (!(element))
					{
						cout<<"Такого элемента нет в списке, проверьте корректность ввода\n";
						_getch();
						break;
					}
					if (!(element->next))
					{
						cout<<"Чтобы добавить элемент в конец списка просто воспользуйтесь функцией под номером '2'\n";
						_getch();
						break;
					}
					MyList.Add_after(element);
				}
				cout <<"Список после изменений: ";MyList.Show(1);
				_getch();
				break;
			}
			case '3':
			{
				int a = 0;
				cout << "1. Вывести список с начала\n2. Вывести список с конца\n";
				while (!(cin >> a) || a<1 || a>2)				//Весь этот вайл - простой cin,
				{												//но модифицированный для работы в switch и других методах класса
					cin.clear();								//ибо простой cin тупо не работает, долго объяснять почему
					while (cin.get() != '\n');					//и тут есть перехват, но это уже второстепенно
					cout << "Некорректный ввод! Повторите!\n";
				}
				cout <<"Список после изменений: ";MyList.Show(a);
				_getch();
				break;
			}
			case '4':
			{
				int a = 0;
				cout << "1. Удалить первый элемент\n2. Удалить последний элемент\n3. Удалить элемент в СЕРЕДИНЕ списка\n";
				while (!(cin >> a) || a<1 || a>3)
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Некорректный ввод! Повторите!\n";
				}
				if (a==1 || a==2)
					MyList.Delete_First_Last(a);
				else
				{
					cout << "Введите элемент который хотите удалить: ";
					string del;
					cin >> del;
					while (!(del.length()))
					{
						cout << "Строка пуста! Повторите ввод!\n";
						cin>>del;
					}
					Chain *element = new Chain;
					element = MyList.Search(del);
					if (!(element))
					{
						cout<<"Такого элемента нет в списке, проверьте корректность ввода\n";
						_getch();
						break;
					}
					if (!(element->next) || !(element->prev))
					{
						cout<<"Чтобы удалить первый или последний элемент списка воспользуйтесь функциями под номерами '1' или '2'\n";
						_getch();
						break;
					}
					MyList.Delete(element);
				}
				cout <<"Список после изменений: ";MyList.Show(1);
				_getch();
				break;
			}
			case '5':
			{
				MyList.~List();
				cout <<"Список после изменений: ";MyList.Show(1);
				_getch();
				break;
			}
			case '6':
			{
				MyList.Special_first();
				_getch();
				break;
			}
			case '7':
			{
				MyList.Special_second();
				cout <<"Список после изменений: ";MyList.Show(1);
				_getch();
				break;
			}
			case '8':
			{
				MyList.StreamInput();
				cout <<"Список после изменений: ";MyList.Show(1);
				_getch();
				break;
			}
			case '9':
			{
				work = false;
				break;
			}
			default:
			{
				cout << "Выберите одну из ДЕВЯТИ предложеных функций!";
				_getch();
			}
		}
	}
	system("pause");
	return 0;
}

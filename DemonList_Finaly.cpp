// DemonList_Finaly.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	}; //�������������� ������ ��� ������

	~List()
	{
		while (Head) //���� �� ������ �� ������ ������ ���-�� ����
		{
			Tail = Head->next; //��������� ����� ������ ���������� ����� ������
			delete Head; //������� ������ �� ������� �����
			Head = Tail; //����� ������ ������ �� ����� ���������� ��������
		}
	}

	void Show(int a)
	{
		Chain *temp;
		if (a == 2)
		{
			//������� ������ � �����
			temp = Tail; //��������� ��������� �� ����� ���������� ��������
			while (temp != NULL) //���� �� ���������� ������ ��������
			{
				cout << temp->stroka << " -> "; //�������� �������� �� �����
				temp = temp->prev; //���������, ��� ����� ����� ����������� ��������
			}
			cout<< "NULL" << "\n";
		}

		if (a == 1)
		{
			//������� ������ � ������
			temp = Head; //�������� ��������� �� ����� ������� ��������
			while (temp != NULL) //���� �� �������� ������ ��������
			{
				cout << temp->stroka << " -> "; //������� ������ ��������� �������� �� �����
				temp = temp->next; //����� ������ �� ����� ���������� ��������
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
		cout << "������� ����� ������� ������: ";
		cin >> x;
		Chain *temp = new Chain; //��������� ������ ��� ����� ������� ���������
		if (a == 1) //� ������ ������
		{
			temp->next = Head;
			if (Head) //���� ������ �� ����
			{
				temp = Head;                 // ��������� � ������ if
				Head->prev = new Chain;
				Head = Head->prev;
				Head->stroka = x;
				Head->next = temp;
				Tail->prev = NULL;
			}
			else //���� ������ ������
			{
				temp->stroka = x;
				temp->prev = NULL; //���������� ������� ��������� � �������
				temp->next = NULL; 
				Head = Tail = temp; //������=�����=��� �������, ��� ������ ��������
			}
		}

		if (a == 2) //� ����� ������
		{
			if (Head) //���� ������ �� ����
			{
				//cout<<"1"<<endl;
				temp = Tail;//��������� ����� ������
				Tail->next = new Chain;//��� �� ��� ��������� �� NULL ������ ����� ��������� �� �����-�� ����.
				Tail = Tail->next;//������ ����� - ��� ��� ����., ��� � ������� ������
				Tail->stroka = x;//���������� � ����� ����� ������ ������� �� �����
				Tail->next = NULL;//��������� ������
				Tail->prev = temp;
			}
			else //���� ������ ������
			{
				//cout<<"2"<<endl;
				temp->stroka = x;
				temp->prev = NULL; //���������� ������� ��������� � �������
				temp->next = NULL; 
				Head = Tail = temp; //������=�����=��� �������, ��� ������ ��������
			}
		}
	}
	
	void Add_after(Chain *afterWord)
	{
		string x;
		cout << "������� ����� ������� ������: ";
		cin >> x;
		Chain *temp = new Chain; //��������� ������ ��� ����� ������� ���������
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
		cout << "������� ������ � ������ � ����� (���������� ����������� �������, ����� - ����������� ��������������): ";
		getline(cin, x);
		while (!(x.length()) || x[x.length()-1]!='.' || x.length()<2)
		{
			cout << "������ ����� ��� ����������� ����� � ����� ������! ��������� ����!\n";
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
				if ((x[i] == ' ' && x[i-1] == ' ') || word == "") //������� �������� � �������� ������: .......
					continue;
				if (Head) //���� ������ �� ����
				{
					//cout<<"1"<<endl;
					temp = Tail;
					Tail->next = new Chain;
					Tail = Tail->next;
					Tail->stroka = word;
					Tail->next = NULL;
					Tail->prev = temp;
				}
				else //���� ������ ������
				{
					//cout<<"2"<<endl;
					temp->stroka = word;
					temp->prev = NULL; //���������� ������� ��������� � �������
					temp->next = NULL; 
					Head = Tail = temp; //������=�����=��� �������, ��� ������ ��������
				}
				word = "";
			}
		}
		//������� ��� �������� ������ ����. � ������ � � ����� ������ (���������� ���� ����� ������ ������ ������� ������ � ����� �����
		//��� ��������� ����� ������ ���� ��������)
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
		cout <<"���� �����:\n";
		while (temp) //���� �� ���������� ������ ��������
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
			temp = temp->next; //���������, ��� ����� ����� ���������� ��������
		}
	}

	void Special_second()
	{
		Chain *temp = Head->next;
		bool goodCheck = false;
		bool goodWord = true;
		string alfa = "abcdefghijklmnopqrstuvwxyz";
		cout <<"���� �����:\n";
		while (temp) //���� �� ���������� ������ ��������
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
			temp = temp->next; //���������, ��� ����� ����� ���������� ��������
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
		cout << "�������� ��� ��� �����:" << endl
			<< "1. ����� ������� � ������" << endl
			<< "2. �������� ������� � ������" << endl
			<< "3. ������� ������ � �������" << endl //���� ��� ������ ��� ���: ���� �� ����� �������� ������ ��� ��� ��� �������� ������� ������ � Show
			<< "4. ������� ������� ������" << endl
			<< "5. ������� ������" << endl
			<< "6. ���������� ��� �����, ������� ���������� �� ������� � ��������� � ������� �������� (a, ab, abc, ...)" << endl
			<< "7. ������� ������ ����� � ���� ������ � ������� ����� �������� �����" << endl
			<< "8. �������� ������ � ����� ������ (��� ��������� ������ ���� ������ ����)" << endl
			<< "9. ��������� ������\n--------------------------------------------------------------------------------------------------------" << endl;
			cout <<"������ �� ���������: "; MyList.Show(1);
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
		c = _getch();
		switch (c)
		{
			case '1':
			{
				cout << "������� �����, ������� ����� ������: ";
				string find_it;
				cin >> find_it;
				Chain *element = new Chain;
				element = MyList.Search(find_it);
				if (!(element))
				{
					cout<<"������ �������� ��� � ������, ��������� ������������ �����\n";
					_getch();
					break;
				}
				cout <<"��� ������� ��������� ����� ����������, ������� ��������� � "<< element->prev <<" � "<<element->next<<" ������� ������"<<endl;
				_getch();
				break;
			}
			case '2':
			{
				int a;
				cout << "1. �������� ������� � ������ ������\n2. �������� ������� � ����� ������\n3. �������� ������� ����� ������-�� �������� � �������� ������\n";
				while (!(cin >> a) || a<1 || a>3)
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "������������ ����! ���������!\n";
				}
				if (a==1 || a==2)
					MyList.Add(a);
				else
				{
					cout << "������� �����, ����� �������� ������ �������� ����� �������: ";
					string after;
					cin >> after;
					while (!(after.length()))
					{
						cout << "������ �����! ��������� ����!\n";
						cin>>after;
					}
					Chain *element = new Chain;
					element = MyList.Search(after);
					if (!(element))
					{
						cout<<"������ �������� ��� � ������, ��������� ������������ �����\n";
						_getch();
						break;
					}
					if (!(element->next))
					{
						cout<<"����� �������� ������� � ����� ������ ������ �������������� �������� ��� ������� '2'\n";
						_getch();
						break;
					}
					MyList.Add_after(element);
				}
				cout <<"������ ����� ���������: ";MyList.Show(1);
				_getch();
				break;
			}
			case '3':
			{
				int a = 0;
				cout << "1. ������� ������ � ������\n2. ������� ������ � �����\n";
				while (!(cin >> a) || a<1 || a>2)				//���� ���� ���� - ������� cin,
				{												//�� ��������������� ��� ������ � switch � ������ ������� ������
					cin.clear();								//��� ������� cin ���� �� ��������, ����� �������� ������
					while (cin.get() != '\n');					//�� � ��� ���� ��������, �� ��� ��� �������������
					cout << "������������ ����! ���������!\n";	//
				}												//
				cout <<"������ ����� ���������: ";MyList.Show(a);
				_getch();
				break;
			}
			case '4':
			{
				int a = 0;
				cout << "1. ������� ������ �������\n2. ������� ��������� �������\n3. ������� ������� � �������� ������\n";
				while (!(cin >> a) || a<1 || a>3)
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "������������ ����! ���������!\n";
				}
				if (a==1 || a==2)
					MyList.Delete_First_Last(a);
				else
				{
					cout << "������� ������� ������� ������ �������: ";
					string del;
					cin >> del;
					while (!(del.length()))
					{
						cout << "������ �����! ��������� ����!\n";
						cin>>del;
					}
					Chain *element = new Chain;
					element = MyList.Search(del);
					if (!(element))
					{
						cout<<"������ �������� ��� � ������, ��������� ������������ �����\n";
						_getch();
						break;
					}
					if (!(element->next) || !(element->prev))
					{
						cout<<"����� ������� ������ ��� ��������� ������� ������ �������������� ��������� ��� �������� '1' ��� '2'\n";
						_getch();
						break;
					}
					MyList.Delete(element);
				}
				cout <<"������ ����� ���������: ";MyList.Show(1);
				_getch();
				break;
			}
			case '5':
			{
				MyList.~List();
				cout <<"������ ����� ���������: ";MyList.Show(1);
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
				cout <<"������ ����� ���������: ";MyList.Show(1);
				_getch();
				break;
			}
			case '8':
			{
				MyList.StreamInput();
				cout <<"������ ����� ���������: ";MyList.Show(1);
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
				cout << "�������� ���� �� ������ ����������� �������!";
				_getch();
			}
		}
	}
	system("pause");
	return 0;
}
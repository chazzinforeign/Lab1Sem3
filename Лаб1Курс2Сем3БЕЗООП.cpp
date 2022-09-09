#include <iostream>
#include <string>
#include <clocale>
#include <ciso646>
#include <locale>

using namespace std;

typedef struct Element
{
	double data;		//�������� ��������
	int col_number;		//����� ������� ��������
	Element* prev;		//��������� �� ���������� ������� � ���������� ������
	Element* next;		//��������� �� ��������� ������� � ���������� ������
} Element;

typedef struct DoubleLinkedList
{ 
	Element *head;		//��������� �� ������ ������
    Element *tail;		//��������� �� ����� ������
} DoubleLinkedList;

typedef struct Table
{
	int n;
	int m;
	DoubleLinkedList *table;
} Table;

Element* CreateElement(int InputColNumber, double InputData)
{
	Element* add_element;

	add_element = new Element;

	add_element->data = InputData;
	add_element->col_number = InputColNumber;
	add_element->prev = NULL;
	add_element->next = NULL;

	return add_element;
}

void PrintElement( Element* element )
{
	cout << element->col_number << "|" << element->data << endl;
}

DoubleLinkedList* CreateDoubleLinkedList( void )
{
	DoubleLinkedList* add_list;

	add_list = new DoubleLinkedList;

	add_list->head = nullptr;
	add_list->tail = nullptr;

	return add_list;
}

void AddElement(DoubleLinkedList* list, int AddColCount, double AddData)
{
	//������� ������� � ���������� �������
	Element* add;

	add = CreateElement(AddColCount, AddData);

	//�������� �� ������� ������ ( ���� ��������� ������ ������� )
	if( list->head == nullptr )
	{
		list->head = add;
		list->tail = add;
		return;
	}

	//������� ��������� cur
	Element* cur = list->head;

	//����� �� ������ ���� �� ������� �� �������, ����� ������� �������� ����� >= ���������� ��� ���� �� ������ �� �����
	while ( (cur->col_number < add->col_number) && (cur != list->tail) )
	{
		cur = cur->next;
	}

	//���� ������� �� ����� ������� ��� ����
	if (cur->col_number == AddColCount)
	{
		//����� �� ���� �������� ���� � �������� �� ���������, ���� ����� ������, ��� ������� �� ���� ������� ��� ����
		cout << "\t\tError!\n" << endl;
		return;
	}

	//���� ��������� � ������ ������
	if ( (cur == list->head) && (add->col_number < cur->col_number) )
	{
		add->next = list->head;
		cur->prev = add;
		list->head = add;
		cout << "\n\tSuccess!\n" << endl;
		return;
	}

	//���� ��������� � ����� ������
	if ( (cur == list->tail) && (add->col_number > cur->col_number) )
	{
		cur->next = add;
		add->prev = cur;
		list->tail = add;
		cout << "\n\tSuccess!\n" << endl;
		return;
	}

	//���� ��������� �� � ������� �� � �����
	add->next = cur;
	add->prev = cur->prev;
	cur->prev->next = add;
	cur->prev = add;
	cout << "\n\tSuccess!\n" << endl;
	return;
}

void ShowList(DoubleLinkedList* list)
{
	if(list->head == nullptr)
	{
		cout << "Row is empty!" << endl;
		return;
	}

	Element* cur = list->head;

	while (cur != list->tail)
	{
		cout << cur->col_number << "|" << cur->data << " -> ";
		cur = cur->next;
	}

	cout << cur->col_number << "|" << cur->data << " -> ";
	return;
}

Table* CreateTable( const int n, const int m)
{
	Table* new_table;

	new_table = new Table;


	new_table -> n = n;
	new_table -> m = m;
		
	new_table -> table = new DoubleLinkedList[ new_table -> n ]; 

	for( int i = 0; i < n; i++)
	{
		new_table->table[ i ].head = new_table->table[ i ].tail = nullptr;
	}

	return new_table;
}

void AddElementInMatrix( Table* add_table, const int add_row_count, const int add_col_count, const double add_data )
{
	if( ( add_row_count > add_table->n ) or (add_col_count > add_table->m) )
	{
		cout << "Error! The entered data exceeds the size of the matrix! " << endl;
		return;
	}

	AddElement( &add_table->table[add_row_count], add_col_count, add_data );
	//cout << "Success! " << endl;
	return;
}

void PrintMatrix(Table* add_table)
{

	for (int i = 0; i < add_table->n; i++)
	{
		cout << "\t" ;
		ShowList(&add_table->table[i]);
		cout << "\n";
	}

	return;
}

void OperationFromTask(Table* add_table)
{

	//������� �� ������ ������� ������
	int i;
	int* vector;
	int positive = 0;
	Element* first;
	Element* second;
	Element* head;
	Element* tail;

		
	//������� �� ������ ������� ������
	vector = new int[add_table->n];

	for( i = 0; i < add_table->n; i++ )
	{
		positive = 0;
		head = add_table->table[i].head;

		if( head != nullptr )
		{
			Element* current = head;
			while( current != nullptr )
			{
				//���� �� ��������� ���� �� ���� ��������������� ������� �� �������� positive = 1
				if( current->data <= 0 )
					positive = 1;
				current = current->next;
			}

			//�������� �� ������ � ������ �� �����, ����� ������ ������� ����� ��������� � ������
				
			if( positive == 0 ) 
			{
				vector[i] = head->data;
						
			}
			else
			{
				Element* current = head;
				while( current->next != nullptr )
					current = current -> next ;

				vector[i] = current -> data;
						
			}
				
		}
	}

	cout << " Matrix is: " << endl << endl;
	PrintMatrix(add_table);
		
	cout << " Vector is: " << endl << endl << "\t";
	//������� ���� ������
	for(i = 0; i <add_table->n; i++)
	{
		head = add_table->table[i].head;
		if( head != nullptr )
			cout << vector[i] << " ";
		else 
			cout << "nth ";
	}

	cout << endl;

	delete(vector);

}

void DeleteMatrix(Table* matrix)
{
	int i;
	Element* curr;
	
	for(i = 0; i < matrix->n; i++)
	{
		curr = matrix->table[i].head;
		while(curr != nullptr)
		{
			if( curr->prev != nullptr )
				delete(curr->prev);
			curr = curr->next;
		}

		delete(matrix->table[i].tail);
	}

	delete(matrix->table);

	delete(matrix);

	return;
}

int Menu(void)
{
	int select;

	do
	{
		system("CLS");
		cout << "\t\tWork with matrix:\n";
		cout << "\t1 - Add new element in matrix\n";
		cout << "\t2 - Operation from the task (change in each row of the matrix the first element is larger than the previous one and the last one is smaller than the previous one)\n";
		cout << "\t3 - Print matrix on a screen\n";		

		cout << "\t0 - End of work\n";
		cin >> select;
	}
	while((select < 0) || (select > 3));

	return select;
}

int main()
{
	setlocale(LC_ALL, "ru");

	int select;
	int row_position;
	int col_position;
	double data;
	int n;
	int m;
	Table* new_matrix;

	do
	{
		cout << "\nEnter the row count(n): " ;
		cin >> n;
		if( n <= 0 )
			cout << "\nError! Try again!" << endl;
	} while(n <= 0);

	do
	{
		cout << "\n\tEnter the col count(m): " ;
		cin >> m;
		if( m <= 0 )
			cout << "\nError! Try again!" << endl;

	} while(m <= 0);
		
	new_matrix = CreateTable( n, m );


	do
	{

		select = Menu();

		switch (select)
		{
			case 1:
				cout << "Enter the item position: "  ;
				do
				{
					cout << "\n\tEnter the row position(0 - n): " ;
					cin >>  row_position;
					if( ( row_position >= new_matrix->n ) || ( row_position < 0 ) )
						cout << "Error!" << endl;
				} while ( ( row_position >= new_matrix->n ) || ( row_position < 0 ) );

				do
				{
					cout << "\n\tEnter the col position(0 - m): " ;
					cin >>  col_position;
					if( ( col_position >= new_matrix->m ) || ( col_position < 0 ) )
						cout << "Error!" << endl;
				} while ( ( col_position >= new_matrix->n ) || ( col_position < 0 ) );

				cout << "\n\tEnter data of element: " ;
				cin >>  data;

				AddElementInMatrix(new_matrix, row_position, col_position, data);

				system("pause");
				break;

			case 2:
				
				OperationFromTask( new_matrix );
				system("pause");
				break;

			case 3:
				PrintMatrix( new_matrix );
				system("pause");
				break;

		}
	} while(select != 0);

	DeleteMatrix(new_matrix);
	system("pause");
	return 0;
}
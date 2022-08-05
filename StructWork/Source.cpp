//			составить программу о книгах в библиотеке
//		структура книги
// номер ”ƒ 
// фамили€ и инициалы автора
// название
// год издани€
// кол-во экземпл€ров
//		программа должна обеспечивать 
// начальное формирование данных обо всех книгах в библиотеке в виде одномерного массива
// добавление данных о книгах вновь поступающих в библиотеку
// удаление данных о списываемых книгах
// по запросу выдаютс€ сведени€ о наличии книг в библиотеке, упор€доченные по годам издани€
//
#include <iostream>
#include <fstream>
#include <conio.h>
#include <io.h>
#include <cstring>
#include <stdio.h>

using namespace std;

struct libary
{
	char numberUDC[20];
	char nameAutor[20];
	char nameBook[20];
	int year;
	int amount;//кол-во экземпл€ров книги
};

libary addBook()
{
	libary temp;

	
	cout << "Enter number of UDC: " << endl;
	gets_s(temp.numberUDC, 20);
	gets_s(temp.numberUDC, 20);
	cout << "Enter name of autor: ";
	gets_s(temp.nameAutor, 20);
	cout << "Enter name of book: ";
	gets_s(temp.nameBook, 20);
	cout << "Enter year: ";
	cin >> temp.year;
	cout << "Enter amount: ";
	cin >> temp.amount;
	return temp;
}

void loaddata_bin(libary* c, int& n)
{
	FILE* f;
	struct _finddata_t myfileinfo;
	const char* filename = "libary.card";
	intptr_t done = _findfirst(filename, &myfileinfo);
	if (done == -1)
	{
		fopen_s(&f, filename, "wb");
		fclose(f);
	}

	fopen_s(&f, filename, "rb");
	while (!feof(f))
	{
		fread(&c[n], sizeof(libary), 1, f);
		n++;
	}
	fclose(f);
	n--;
}

void savedata_bin(libary* c, int& n)
{
	FILE* f;
	const char* filename = "libary.card";

	fopen_s(&f, filename, "wb");
	fwrite(&c[0], sizeof(libary), n, f);
	fclose(f);
}

void printAllBooks(libary* c, int &n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << "Number of UDC: " << c[i].numberUDC << endl;
		cout << "Name of Autor: " << c[i].nameAutor << endl;
		cout << "Name of Book: " << c[i].nameBook << endl;
		cout << "Year : " << c[i].year << endl;
		cout << "Amount : " << c[i].amount << endl;
	}
	system("pause");
}

void printAllBooksByYears(libary* c, int& n)
{
	//сортировка книг по году
	libary temp;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j<n;j++)
			if (c[j - 1].year > c[j].year)
			{
				temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
	//}

	////печать всех книг
	//for (size_t i = 0; i < n; i++)
	//{
	//	cout << "Number of UDC: " << c[i].numberUDC << endl;
	//	cout << "Name of Autor: " << c[i].nameAutor << endl;
	//	cout << "Name of Book: " << c[i].nameBook << endl;
	//	cout << "Year : " << c[i].year << endl;
	//	cout << "Amount : " << c[i].amount << endl;
	//}
	system("pause");
}

void pushBook(libary* c, int& n)
{
	libary newbook;
	newbook = addBook();
	c[n] = newbook;
	n++;
}

void deleteBook(libary* c, int &n)
{
	libary failBook;
	int k = - 1;
	cout << "Enter name of fail book: ";
	cin >> failBook.nameBook;
	for (size_t i = 0; i < n; i++)
	{
		if (strcmp(c[i].nameBook,failBook.nameBook) == 0)
		{
			k = i;
		}
	}
	if (k >= 0)
	{
		for (size_t i = k; i < n - 1; i++)
			c[i] = c[i + 1];
		n--;
	}

}

int main()
{
	libary c[1000];
	int n = 0;
	int k;
	loaddata_bin(c, n);
	do
	{
		system("CLS");
		cout << "1 - print all book" << endl;
		cout << "2 - add book" << endl;
		cout << "3 - delete book" << endl;
		cout << "4 - print all book by year" << endl;
		cout << "0 - quit" << endl;
		cin >> k;
		switch (k) {
		case 1: 
			printAllBooks(c, n);
			break;
		case 2:	
			pushBook(c, n);
			break;
		case 3:
			deleteBook(c, n);
			break;
		case 4:
			printAllBooksByYears(c, n);
			break;
		}
	} while (k != 0);

	savedata_bin(c, n);

	return 0;
}
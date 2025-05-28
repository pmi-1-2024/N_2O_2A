#ifndef LIBRARYBOOK_H
#define LIBRARYBOOK_H
#include <iostream>
#include <deque>
#include "Book.h"
using namespace std;
class LibraryBook
{
private:
	int Book_ID, number;
public:
	LibraryBook();
	LibraryBook(int Bid, int c);
	int GetID()const;
	int GetNumber()const;
	string getName(deque<Book*>books)const;
	bool validateBookId(const int& bookId, deque<Book*>& books);
	void SetNumber(int c);
	void ConsolePrint(deque<Book*>books)const;
	void ConsoleInput(deque<Book*>& books);
	friend istream& operator >>(istream& is, LibraryBook& lb);
	friend ostream& operator <<(ostream& os, const LibraryBook& lb);
};
#endif
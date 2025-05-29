#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include "LibraryBook.h"
#include <deque>
#include <string>
#include "Book.h"

using namespace std;
class Library
{
private:
	string ID, name, address;
	deque<LibraryBook> libBooks;
public:
	Library();
	Library(string id, string n, string ad);
	string GetID()const;
	string GetName()const;
	string GetAddress()const;
	deque<LibraryBook>& GetBooks();
	void PrintToFile(ostream& out) const;
	void SetName(string& n);
	void SetAddress(string& add);
	void ConsolePrint(deque<Book*>books)const;
	friend istream& operator >>(istream& is, Library& lib);
	friend ostream& operator <<(ostream& os, const Library& lib);
	void ShowBooks(deque<Book*>books) const;
};
#endif
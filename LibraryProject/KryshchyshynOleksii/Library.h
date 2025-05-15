#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include "LibraryBook.h"
#include <deque>
#include <string>
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
	void SetName(string& n);
	void SetAddress(string& add);
	friend istream& operator >>(istream& is, Library& lib);
	friend ostream& operator <<(ostream& os, const Library& lib);
	void AddBook(const LibraryBook& book);
	bool RemoveBookByID(const int& bookid); 
	void ShowBooks() const;
};
#endif

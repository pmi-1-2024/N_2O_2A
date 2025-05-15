#ifndef LIBRARYBOOK_H
#define LIBRARYBOOK_H
#include <iostream>
using namespace std;
class LibraryBook
{
private:
	int Book_ID, number;
public:
	LibraryBook();
	LibraryBook(int Bid, int c);
	int GetID()const;
	void SetNumber(int& c);
	void ConsolePrint()const;
	void ConsoleInput();
	friend istream& operator >>(istream& is, LibraryBook& lb);
	friend ostream& operator <<(ostream& os, const LibraryBook& lb);
};
#endif

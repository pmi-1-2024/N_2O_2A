#include "LibraryBook.h"

LibraryBook::LibraryBook() : Book_ID(int()), number(0) {}

LibraryBook::LibraryBook(int Bid, int c) : Book_ID(Bid), number(c) {}

int LibraryBook::GetID() const
{
	return Book_ID;
}

void LibraryBook::SetNumber(int& c)
{
	number = c;
}

void LibraryBook::ConsolePrint() const
{
	cout << "\nBook: " << Book_ID << ", number of books: " << number;
}

void LibraryBook::ConsoleInput()
{
	cout << "\nEnter book ID: ";
	cin >> Book_ID;
	cout << "\nEnter number of books: ";
	cin >> number;
}

istream& operator>>(istream& is, LibraryBook& lb)
{
	is >> lb.Book_ID >> lb.number;
	return is;
}

ostream& operator<<(ostream& os, const LibraryBook& lb)
{
	os << lb.Book_ID << " " << lb.number;
	return os;
}

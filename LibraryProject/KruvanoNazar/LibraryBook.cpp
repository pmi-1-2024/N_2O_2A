#include "LibraryBook.h"

LibraryBook::LibraryBook() : Book_ID(int()), number(0) {}

LibraryBook::LibraryBook(int Bid, int c) {
	if (Bid <= 0) throw invalid_argument("Book ID must be positive");
	if (c < 0) throw invalid_argument("Number of books cannot be negative");
	Book_ID = Bid;
	number = c;
}
int LibraryBook::GetID() const
{
	return Book_ID;
}

int LibraryBook::GetNumber()const {
	return number;
}

string LibraryBook::getName(deque<Book*> books) const
{
	for (auto& book : books) {
		if (Book_ID == book->getID()) {
			return book->getName();
			break;
		}
	}
	return "noname";
}

bool LibraryBook::validateBookId(const int& bookId, deque<Book*>& books)
{
	for (auto& book : books) {
		if (book->getID() == bookId) {
			return true;
		}
	}
	return false;
}

void LibraryBook::SetNumber(int c)
{
	if (c < 0) throw invalid_argument("Number of books cannot be negative");
	number = c;
}

void LibraryBook::ConsolePrint(deque<Book*>books) const
{
	cout << "\nBook " << Book_ID << ":" << getName(books) << ", number of books: " << number;
}

void LibraryBook::ConsoleInput(deque<Book*>& books)
{
	bool valid = false;

	do {
		cout << "\nEnter book ID: ";
		cin >> Book_ID;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw invalid_argument("Invalid input for Book ID");
		}

		valid = validateBookId(Book_ID, books);
		if (!valid) {
			cout << "This book does not exist, please try again.\n";
		}
	} while (!valid);

	cout << "\nEnter number of books: ";
	cin >> number;

	if (cin.fail() || number < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Invalid number of books");
	}
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
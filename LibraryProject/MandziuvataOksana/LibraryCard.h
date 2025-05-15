#ifndef LIBRARYCARD_H
#define LIBRARYCARD_H
#include <iostream>
#include <string>
#include "Role.h"
#include <deque>
#include "Library.h"
class LibraryCard{
private:
	string library_ID;
	Role role;
public:
	LibraryCard();
	LibraryCard(string lID, Role r);
	string GetLibID()const;
	Role GetRole()const;
	bool ValidateID(deque<Library>& libs);
	void SetRole(Role& r);
	void ConsolePrint()const;
	void ConsoleInput();
	friend istream& operator>>(istream& is, LibraryCard& lc);
	friend ostream& operator<<(ostream& os, const LibraryCard& lc);
};
#endif

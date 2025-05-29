#ifndef LIBRARYUSER_H
#define LIBRARYUSER_H
#include <iostream>
#include <string>
#include "LibraryCard.h"
#include <deque>
#include "User.h"
#include "Library.h"
using namespace std;

class LibraryUser{
private:
	string user_id;
	LibraryCard libcard;
public:
	LibraryUser();
	LibraryUser(string id, LibraryCard lc);
	User getUser(deque<User>&users);
	Library& getLibrary(deque<Library>& libs);
	string GetLibUserID()const;
	LibraryCard &GetLibCard();
	void ConsolePrint()const;
	bool operator==(LibraryUser& other) const;
	friend istream& operator >>(istream& is, LibraryUser& lbu);
	friend ostream& operator <<(ostream& os, const LibraryUser& lbu);
};
#endif
  
#ifndef LIBRARYUSER_H
#define LIBRARYUSER_H
#include <iostream>
#include <string>
#include "LibraryCard.h"
#include <deque>
#include "User.h";
using namespace std;

class LibraryUser{
private:
	string user_id;
	LibraryCard libcard;
	bool ValidateUserID(deque<User>&users);
public:
	LibraryUser();
	LibraryUser(string id, LibraryCard lc);
	string GetLibUserID()const;
	LibraryCard GetLibCard()const;
	void ConsolePrint()const;
	friend istream& operator >>(istream& is, LibraryUser& lbu);
	friend ostream& operator <<(ostream& os, const LibraryUser& lbu);
};
#endif

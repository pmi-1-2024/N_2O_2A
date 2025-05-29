#include "LibraryUser.h"

LibraryUser::LibraryUser() : user_id(""), libcard(LibraryCard()) {}

LibraryUser::LibraryUser(string id, LibraryCard lc) : user_id(id), libcard(lc) {}

User LibraryUser::getUser(deque<User>& users)
{
	for (auto& user : users) {
		if (user_id == user.GetUserId()) {
			return user;
		}
	}
	throw runtime_error("User not found for LibraryUser ID: " + user_id);
}

Library &LibraryUser::getLibrary(deque<Library>& libs)
{
	for (auto& lib : libs) {
		if (GetLibCard().GetLibID() == lib.GetID()) {
			return lib;
		}
	}
	throw runtime_error("Library not found for LibraryUser ID: " + user_id);
}

string LibraryUser::GetLibUserID() const
{
	return user_id;
}

LibraryCard &LibraryUser::GetLibCard()
{
	return libcard;
}

void LibraryUser::ConsolePrint() const
{
	cout << "\nLibrary user: " << user_id;
	libcard.ConsolePrint();
}

bool LibraryUser::operator==( LibraryUser& other) const
{
		return user_id == other.user_id && libcard.GetLibID() == other.libcard.GetLibID() && libcard.GetRole() == other.GetLibCard().GetRole();
}

istream& operator>>(istream& is, LibraryUser& lbu)
{
	 is >> lbu.user_id >> lbu.libcard;
	return is;
}

ostream& operator<<(ostream& os, const LibraryUser& lbu)
{
	os <<"\n"<< lbu.user_id << " " << lbu.libcard;
	return os;
}

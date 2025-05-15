#include "LibraryUser.h"

bool LibraryUser::ValidateUserID(deque<User>& users)
{
	for (auto& user : users) {
		if (user_id == user.GetUserId()) {
			return true;
		}
	}
	cout << "\nYou entered a non-existent id.";
	return false;
}

LibraryUser::LibraryUser() : user_id(""), libcard(LibraryCard()) {}

LibraryUser::LibraryUser(string id, LibraryCard lc) : user_id(id), libcard(lc) {}

string LibraryUser::GetLibUserID() const
{
	return user_id;
}

LibraryCard LibraryUser::GetLibCard() const
{
	return libcard;
}

void LibraryUser::ConsolePrint() const
{
	cout << "\nLibrary user: " << user_id;
	cout << "\nLibrary card: ";
	libcard.ConsolePrint();
}

//void LibraryUser::ConsoleInput()
//{
//	cout << "\nEnter your ID:";
//	cin >> user_id;
//	cout << "\nEnter library card data: ";
//	libcard.ConsoleInput();
//}

istream& operator>>(istream& is, LibraryUser& lbu)
{
	 is >> lbu.user_id >> lbu.libcard;
	return is;
}

ostream& operator<<(ostream& os, const LibraryUser& lbu)
{
	os << lbu.user_id  << lbu.libcard;
	return os;
}

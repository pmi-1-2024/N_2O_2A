#include "LibraryCard.h"

bool LibraryCard::ValidateID(deque<Library>& libs)
{
	for (auto& lib : libs) {
		if (library_ID == lib.GetID()) {
			return true;
		}
	}
	cout << "\nThis library does not exist.";
	return false;
}

LibraryCard::LibraryCard() : library_ID(""), role(Role()) {}

LibraryCard::LibraryCard(string lID, Role r) : library_ID(lID), role(r) {}

string LibraryCard::GetLibID() const
{
	return library_ID;
}

Role LibraryCard::GetRole() const
{
	return role;
}

void LibraryCard::SetRole(Role& r) {
	role = r;
}

void LibraryCard::ConsolePrint() const
{
	cout << "\nLibrary card: ";
	cout << "\nLibrary: " << library_ID;
	cout << "\nRole:"; role.ConsolePrint();
}

void LibraryCard::ConsoleInput()
{
	cout << "\nEnter library ID: ";
	cin >> library_ID;
	cout << "\nEnter role data: ";
	role.ConsoleRead();
}

istream& operator>>(istream& is, LibraryCard& lc)
{
	is >> lc.library_ID  >> lc.role;
	return is;
}

ostream& operator<<(ostream& os, const LibraryCard& lc)
{
	os << lc.library_ID  << lc.role;
	return os;
}

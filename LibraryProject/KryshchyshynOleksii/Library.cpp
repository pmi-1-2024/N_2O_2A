#include "Library.h"

Library::Library() : ID(""), name(""), address("") {}

Library::Library(string id, string n, string ad)
    : ID(id), name(n), address(ad) {}

string Library::GetID() const {
    return ID;
}

string Library::GetName() const {
    return name;
}

string Library::GetAddress() const {
    return address;
}

deque<LibraryBook>& Library::GetBooks()
{
    return libBooks;
}

void Library::SetName(string& n) {
    name = n;
}

void Library::SetAddress(string& add) {
    address = add;
}

void Library::AddBook(const LibraryBook& book)
{
    libBooks.push_back(book);
}

bool Library::RemoveBookByID(const int& bookid)
{
    for (auto it = libBooks.begin(); it != libBooks.end(); it++) {
        if (it->GetID() == bookid) {
            libBooks.erase(it);
            return true;
        }
    }
    return false;
}

void Library::ShowBooks() const
{
    cout << "\nLibrary`s book list: ";
    for (auto& book : libBooks) {
        cout << "\n ";
        book.ConsolePrint();
    }
}

istream& operator>>(istream& is, Library& lib) {
    size_t numbooks;
    is >> lib.ID, is.ignore(), getline(is, lib.name,';'), getline(is, lib.address);
    is >> numbooks;
    for (size_t i = 0; i < numbooks; i++) {
        LibraryBook libbook;
        is >> libbook;
        lib.libBooks.push_back(libbook);
    }
    return is;
}

ostream& operator<<(ostream& os, const Library& lib) {
    os << "\nID: " << lib.ID;
    os << "\nName: " << lib.name;
    os << "\nAddress: " << lib.address;
    os << "\nNumber of books in this library: " << lib.libBooks.size();
    return os;
}

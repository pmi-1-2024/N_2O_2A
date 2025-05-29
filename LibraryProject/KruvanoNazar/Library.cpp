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
    if (n.empty()) throw invalid_argument("Library name cannot be empty");
    name = n;
}

void Library::SetAddress(string& add) {
    if (add.empty()) throw invalid_argument("Library address cannot be empty");
    address = add;
}

void Library::ConsolePrint(deque<Book*>books)const
{
    cout << "\nLibrary " << ID << ": " << name << ", " << address;
    ShowBooks(books);
}


void Library::PrintToFile(ostream& out) const {
    out << ID << " " << name << ";" << address << "\n";
    out << libBooks.size() << "\n";
    for (const auto& book : libBooks) {
        out << book << "\n";
    }
}

void Library::ShowBooks(deque<Book*>books) const{
    cout << "\nLibrary`s book list: ";
    cout << "\n ";
    for (auto& book : libBooks) {
        book.ConsolePrint(books);
    }
}
istream& operator>>(istream& is, Library& lib) {
    size_t numbooks;
    is >> lib.ID, is.ignore(), getline(is, lib.name, ';'), getline(is, lib.address);
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
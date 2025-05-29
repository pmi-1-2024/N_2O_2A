#include <iostream>
#include "Features.h"
int main()
{
    try {
        deque<Book*> Books;
        deque<Library> libs;
        deque<User> users;
        deque<LibraryUser> libusers;
        deque<Order> orders;
        ifstream file1("books.txt");
        ifstream file2("users.txt");
        ifstream file3("librarys_users.txt");
        ifstream file4("orders.txt");
        ifstream file5("libraries.txt");
        ReadBooksFromFile(file1, Books);
        ReadFromFile(file2, users);
        ReadFromFile(file3, libusers);
        ReadFromFile(file4, orders);
        ReadFromFile(file5, libs);

        MainProgram(users, Books, libs, libusers, orders);
        return 0;
    }
    catch (runtime_error& e) {
        cerr << e.what();
        return 1;
    }
    catch (invalid_argument& e) {
        cerr << e.what();
    }
    catch (...) {
        cerr << "Unknown error! ";
        return 1;
    }
}

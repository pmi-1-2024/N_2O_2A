#ifndef FEATURES_H
#define FEATURES_H
#include "ElectronicBook.h"
#include "PaperBook.h"
#include <fstream>
#include <deque>
#include "User.h"
#include "LibraryCard.h"
#include "LibraryUser.h"
#include "Order.h"
void ReadBooksFromFile(ifstream& file, deque<Book*>&books);
template<typename T>
void ReadFromFile(ifstream& file, deque<T>& dequ);
void AddBookToFile(const string& filename, deque<Book*>& books);
void SaveLibrariesToFile(deque<Library>& libraries, const string& filename);
void SaveOrdersToFile(deque<Order>& orders, const string& filename);
void UpdateBookInfo(Library& lib, const string& filename, deque<Library>& libs);
void SaveLibUsersToFile(deque<LibraryUser>& libusers, const string& filename);
void ShowOrders(bool&findAny,deque<Order>& orders, LibraryUser& libusr);
void RemoveOrderById(const string& filename, LibraryUser& libusr, deque<Order>& orders);
bool RemoveBookByID(const int& bookid, const string& filename, Library& lib, deque<Library>& libs);
void AddBook(const LibraryBook& book, deque<Library>& libs, const string& filename, Library& lib);
template<typename T>
void AddToFile(const string& filename, T& u);
void startmenu();
void CustomerMenu();
void LibrarianMenu();
void AdminMenu();
void CustomerFuncMenu(LibraryUser& luser, bool& in_account, deque<User>& users, deque<LibraryUser>& libusers, deque<Library>& libs, deque<Book*>& books, deque<Order>& orders);
void LibrarianFuncMenu(LibraryUser& luser, bool& in_account, deque<Library>& libs, deque<Book*>& books, deque<Order>& orders);
void AdminFuncMenu(LibraryUser& luser, bool& in_account, deque<LibraryUser>& libusers, deque<Library>& libs);
void UserMenu(User& user1,bool& in_account,deque<User>& users,deque<LibraryUser>& libusers,deque<Library>& libs,deque<Book*>& books,deque<Order>& orders);
void MainProgram(deque<User>& users, deque<Book*>& books, deque<Library>& libs, deque<LibraryUser>& libusers, deque<Order>& orders);
void BookBrowsingMenu(int & bookid, LibraryUser&libuser, deque<Library>& libs, deque<Book*>& books);
User Logining(int &counter,bool &access,deque<User>& users, const string &em, const string& pass);
LibraryCard CreateLibCard(deque<Library>&libs);
LibraryUser BecomeLibUs(const User& us,deque<Book*>books,deque<LibraryUser>&libusers, deque<Library>&libs);
void PlaceAnOrder(LibraryUser& libuse,deque<Order>& orders,deque<Library>&libs);
bool LibraryUserExists(const LibraryUser& target, const deque<LibraryUser>& libusers);
void Registration(deque<User>& users);

template<typename T>
inline void ReadFromFile(ifstream& file, deque<T>& dequ)
{
	if (!file.is_open()) throw runtime_error("Eror: Can`t open this file");
		size_t size;
		file >> size;
		for (size_t i = 0; i < size; i++) {
			T temp;
			file >> temp;
			dequ.push_back(temp);
		}
}

template<typename T>
inline void AddToFile(const string& filename, T& u)
{
	fstream file(filename, ios::in | ios::out);
	if (!file.is_open()) throw runtime_error("Can`t open file for writing");
	size_t count;
	file >> count;
	count++;
	file.seekp(0, ios::beg);
	file << count << "\n";
	file.seekp(0, ios::end);
	file << u;
}
template <typename T>
T SafeInput(const string& prompt) {
	T value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (!cin.fail()) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			return value;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[ERROR] Invalid input. Please try again: ";
	}
}
#endif
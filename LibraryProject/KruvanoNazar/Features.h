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
template<typename T>
void AddToFile(const string& filename, T& u);
void startmenu();
void CustomerMenu();
void BookBrowsingMenu(int & bookid, LibraryUser&libuser, deque<Library>& libs, deque<Book*>& books);
User Logining(int &counter,bool &access,deque<User>& users, const string &em, const string& pass);
LibraryCard CreateLibCard(deque<Library>&libs);
LibraryUser BeacomeLibUs(const User& us,deque<LibraryUser>&libusers, deque<Library>&libs);
void PlaceAnOrder(LibraryUser& libuse,deque<Order>& orders,deque<Library>&libs);
bool LibraryUserExists(const LibraryUser& target, const deque<LibraryUser>& libusers);
void Registration(deque<User>& users);
#endif

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
	file << u << "\n ";
}

#include "Features.h"

void ReadBooksFromFile(ifstream& file, deque<Book*>& books)
{
	if (!file.is_open()) throw runtime_error("Eror: Can`t open this file");
	int type;
	if (!books.empty()) {
		for (Book* bd : books) {
			delete bd;
		}
		books.clear();
	}
	size_t size;
	file >> size;
	Book* b = nullptr;
	for (size_t i = 0; i < size; i++) {
		file >> type;
		switch (type) {
		case 1:
			b = new PaperBook();
			break;
		case 2:
			b = new ElectronicBook();
			break;
		}
		file >> *b;
		books.push_back(b);
	}
}

void AddBookToFile(const string& filename, deque<Book*>& books)
{
	fstream file(filename, ios::in | ios::out);
	if (!file.is_open()) throw runtime_error("Can`t open file for writing");
	size_t count;
	file >> count;
	count++;
	file.seekp(0, ios::beg);
	file << count << "\n";
	file.seekp(0, ios::end);
	cout << "Enter book type (1 - Paper, 2 - Electronic): ";
	int type;
	cin >> type;
	if (type <= 0 || type >= 3) throw invalid_argument("Type must be 1 or 2");
	Book* pb = nullptr;
	switch (type) {
	case 1:
		pb= new PaperBook();
		break;
	case 2:
		pb = new ElectronicBook();
		break;
	}
	pb->ConsoleInput();
	books.push_back(pb);
	cout << "\nNew book added to deque successfully!";
	file << type <<" " << *pb << "\n";
	cout << "\nNew book added to file successfully!";
}

void SaveLibrariesToFile(deque<Library>& libraries, const string& filename)
{
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		throw runtime_error("Eror: Can not open library file to change");
	}
	outFile << libraries.size() << "\n";
	for (auto& lib : libraries) {
		lib.PrintToFile(outFile);
	}
	outFile.close();
}

void SaveOrdersToFile(deque<Order>& orders, const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		throw runtime_error("Eror: Can not open library file to change");
	}

	outFile << orders.size();
	for (auto& ord : orders) {
		outFile << ord;
	}

	outFile.close();
}


void UpdateBookInfo(Library& lib, const string& filename, deque<Library>& libs)
{
	int bookID = SafeInput<int>("\nEnter the ID of the book you want to update: ");
	bool found = false;

	for (auto& book : lib.GetBooks())
	{
		if (book.GetID() == bookID)
		{
			found = true;

			int newCount;
			cout << "Current count: " << book.GetNumber() << "\n";
			cout << "Enter new count: ";
			cin >> newCount;

			book.SetNumber(newCount);
			cout << "Book count updated successfully.\n";
			SaveLibrariesToFile(libs, filename);
			break;
		}
	}

	if (!found)
	{
		cout << "Book with ID " << bookID << " not found in the library.\n";
	}

}

void SaveLibUsersToFile(deque<LibraryUser>& libusers, const string& filename){
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		throw runtime_error("Eror: Can not open library file to change");
	}

	outFile << libusers.size();
	for (auto& luser : libusers) {
		outFile << luser;
	}

	outFile.close();
}

void ShowOrders(bool&findAny,deque<Order>& orders, LibraryUser& libusr)
{
	findAny = false;
	for (const auto& order : orders) {
		if (order.getLibId() == libusr.GetLibCard().GetLibID()) {
			order.ConsolePrint();
			cout << "\n-------------------------\n";
			findAny = true;
		}
	}
}

void RemoveOrderById(const string& filename, LibraryUser& libusr, deque<Order>& orders)
{
	string libID = libusr.GetLibCard().GetLibID();

	cout << "\nYour orders in this library:\n";
	bool foundAny = false;

	ShowOrders(foundAny,orders, libusr);

	if (!foundAny) {
		cout << "You have no orders in this library.\n";
		return;
	}

	int orderIdToDelete = SafeInput<int>("\nEnter the ID of the order to delete: ");

	bool deleted = false;
	for (auto it = orders.begin(); it != orders.end(); ++it) {
		if (it->getOrderId() == orderIdToDelete &&
			it->getLibId() == libID)
		{
			orders.erase(it);
			SaveOrdersToFile(orders, filename);
			deleted = true;
			cout << "Order deleted successfully.\n";
			break;
		}
	}

	if (!deleted) {
		cout << "No matching order found with ID " << orderIdToDelete << ".\n";
	}

}

bool RemoveBookByID(const int& bookid, const string& filename, Library& lib, deque<Library>& libs)
{
		for (auto it = lib.GetBooks().begin(); it != lib.GetBooks().end(); ++it) {
			if (it->GetID() == bookid) {
				lib.GetBooks().erase(it);
				SaveLibrariesToFile(libs, filename);
				return true;
			}
		}

		return false;
}

void AddBook(const LibraryBook& book, deque<Library>& libs, const string& filename, Library& lib)
{
	lib.GetBooks().push_back(book);
	SaveLibrariesToFile(libs, filename);
	cout << "Book added to library and file updated.\n";
}

void Registration(deque<User>& users)
{
	bool valid=true;
	User us;
	do {
		do {
			us.ConsoleInput();
		} while (us.ValidateEmail() != true);
		for (auto& user : users) {
			if (us == user) valid = false;
		}
		if(!valid) cout << "\nAccount with this ID already exists,please try again";
	} while (!valid);
	users.push_back(us);
	cout << "\nYour account is registered!";
	AddToFile("users.txt", us);
}
bool LibraryUserExists( LibraryUser& target, const deque<LibraryUser>& libusers) {
	for (const auto& user : libusers) {
		if (user == target) return true;
	}
	return false;
}
User Logining(int&counter ,bool &access,deque<User>& users, const string& em, const string& pass)
{
	for (auto& us : users) {
		if (us.GetEmail() == em && us.CheckPassword(pass) == true) {
			cout << "\nWelcome to your account!";
			access = true;
			return us;
		}
	}
	if (!access) {
	cout << "\nYou entered an incorrect email or password, please try again";
	counter++;
	}
	return User();
}
LibraryCard CreateLibCard(deque<Library>& libs)
{

	LibraryCard lc;
	bool valid;
	do {
		lc.ConsoleInput();
		valid = lc.ValidateID(libs);
		if (!valid) {
			cout << "\nInvalid library id, please try again.";
		}
	} while (!valid);
	return lc;
}
LibraryUser BecomeLibUs(const User& us,deque<Book*>books,deque<LibraryUser>&libusers, deque<Library>& libs)
{
	for (auto& lib : libs) {
		cout << "\n";
		lib.ConsolePrint(books);
	}
	LibraryUser libus;
	while (true) {
	
		LibraryCard lc = CreateLibCard(libs);
		libus = LibraryUser(us.GetUserId(), lc);

		if (LibraryUserExists(libus, libusers)) {
			cout << "\nYou are already registered in this library. Try another one.";
			continue;
		}
		break;
	}

	cout << "You have successfully become a client of the library " << libus.GetLibCard().GetLibID() << ": " << libus.getLibrary(libs).GetName();
	libusers.push_back(libus);
	AddToFile("librarys_users.txt", libus);

	return libus;
}
void PlaceAnOrder( LibraryUser& libuse, deque<Order>& orders, deque<Library>& libs)
{
	Order od;
	bool accesstoplace = false;
	od.ConsoleInput();
	od.SetUserID(libuse.GetLibUserID());
	od.SetLibID(libuse.GetLibCard().GetLibID());
	for (auto& libbok : libuse.getLibrary(libs).GetBooks()) {
			if (od.getBookID() == libbok.GetID()) {
				accesstoplace = true;
				cout << "\nYou have successfully checked out a book from the library!";
				orders.push_back(od);
				AddToFile("orders.txt", od);
				break;
			}
	}
	if (!accesstoplace) cout << "\nError: book ID not found in your library.";
}
void startmenu()
{
	cout << "\nWelcome!";
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit";
	cout << "\n1. Log in";
	cout << "\n2. Sign up";
}
void CustomerMenu()
{
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit";
	cout << "\n1. Return to login menu";
	cout << "\n2. View libraries where I am registered";
	cout << "\n3. View books in my library";
	cout << "\n4. Place an order for a book";
}
void LibrarianMenu()
{
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit program";
	cout << "\n1. Log out from LibraryUser account";

	cout << "\n\n--- Book Management ---";
	cout << "\n2. View all books in my library";
	cout << "\n3. Add a new book";
	cout << "\n4. Edit book details";
	cout << "\n5. Delete a book";

	cout << "\n\n--- Order Management ---";
	cout << "\n6. View orders";
	cout << "\n7. Cancel an order";
}
void AdminMenu()
{
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit";
	cout << "\n1. Return to login menu";
	cout << "\n2. Set user role";
	cout << "\n3. Change library info";
}

void BookBrowsingMenu(int& bookid,LibraryUser& libuser,deque<Library>&libs, deque<Book*>& books)
{
	bool BookInLibrary = false;
	for (auto& libbook : libuser.getLibrary(libs).GetBooks()) {
		if (libbook.GetID() == bookid) {
			BookInLibrary = true;
			break;
		}
	}
	if (!BookInLibrary) {
		cout << "\nThere is no book with this ID in your library!";
		return;
	}
	for (Book* b : books) {
		if (b->getID() == bookid) {
			b->Consoleprint();
			return;
		}
	}
	cout << "\nA book with this ID does not exist!";
}
void CustomerFuncMenu(
	LibraryUser& luser,
	bool& in_account,
	deque<User>& users,
	deque<LibraryUser>& libusers,
	deque<Library>& libs,
	deque<Book*>& books,
	deque<Order>& orders)
{
	bool in_library = true;

	while (in_library) {
		CustomerMenu();
		int lib_choice = SafeInput<int>("\nEnter choice: ");

		switch (lib_choice) {
		case 0: {
			cout << "\nLogged out.";
			in_account = false;
			in_library = false;
			break;
		}
		case 1: {
			cout << "\nReturning to previous menu...";
			in_library = false;
			break;
		}
		case 2: {
			cout << "\nLibraries where I am registered:\n";
			for (auto& libus : libusers) {
				if (libus.GetLibUserID() == luser.GetLibUserID()) {
					libus.GetLibCard().ConsolePrint();
					cout << "\n";
				}
			}
			break;
		}
		case 3: {
			cout << "\n";
			luser.getLibrary(libs).ShowBooks(books);
			cout << "\nWould you like more info about a book?\n1. No\n2. Yes";
			cout << "\nEnter your choice: ";
			int choice = SafeInput<int>("\nEnter your choice:");
			if (choice == 2) {
				int bookid;
				cout << "\nEnter book ID: ";
				cin >> bookid;
				BookBrowsingMenu(bookid, luser, libs, books);
			}
			break;
		}
		case 4: {
			PlaceAnOrder(luser, orders, libs);
			break;
		}
		default:
			cout << "\nInvalid option.";
			break;
		}
	}
}
void LibrarianFuncMenu(
	LibraryUser& luser,
	bool& in_account,
	deque<Library>& libs,
	deque<Book*>& books,
	deque<Order>& orders)
{
	bool in_library = true;

	while (in_library) {
		LibrarianMenu();
		int lib_choice = SafeInput<int>("\nEnter choice: ");

		switch (lib_choice) {
		case 0:
			cout << "\nLogged out.";
			in_account = false;
			in_library = false;
			break;

		case 1: {
			cout << "\nReturning to previous menu...";
			in_library = false;
			break;
		}
		case 2: {
			luser.getLibrary(libs).ShowBooks(books);
			break;
		}
		case 3: {
			LibraryBook tempBook;
			tempBook.ConsoleInput(books);
			AddBook(tempBook, libs, "libraries.txt", luser.getLibrary(libs));
			break;
		}
		case 4: {
			UpdateBookInfo(luser.getLibrary(libs), "libraries.txt", libs);
			break;
		}
		case 5: {
			luser.getLibrary(libs).ShowBooks(books);
			int id = SafeInput<int>("\nPlease enter id of book to remove: ");
			RemoveBookByID(id, "libraries.txt", luser.getLibrary(libs), libs);
			cout << "\nThe book has been removed from your library";
			break;
		}
		case 6: {
			bool findAny = false;
			ShowOrders(findAny,orders, luser);
			if (!findAny) {
				cout << "You have no orders in this library.\n";
				break;
			}
			break;
		}
		case 7: {
			RemoveOrderById("orders.txt", luser, orders);
			break;
		}

		default:
			cout << "\nInvalid option.";
			break;
		}
	}
}
void AdminFuncMenu(LibraryUser& luser, bool& in_account, deque<LibraryUser>& libusers, deque<Library>& libs)
{
	cout << "\nWelcome to your library account!";
	bool in_library = true;

	while (in_library) {
		AdminMenu();
		int lib_choice = SafeInput<int>("\nEnter choice: ");
		switch (lib_choice) {
		case 0:
			cout << "\nLogged out.";
			in_account = false;
			in_library = false;
			break;

		case 1:
			cout << "\nReturning to previous menu...";
			in_library = false;
			break;

		case 2: {

			cout << "\nUsers of this library:";
			for (auto& libus : libusers) {
				if (libus.GetLibCard().GetLibID() == luser.GetLibCard().GetLibID())
					libus.ConsolePrint();
			}
			string inpUID;
			int inpRID;
			bool idvalid = false;
			Role temprole;
			bool valid_role = false;
			while (!idvalid) {
				cout << "Enter user's ID to change role: ";
				cin >> inpUID;
				if (inpUID != luser.GetLibUserID()) {
					cout << "\nYou can`t change your role!";
				}
				else {
					idvalid = true;
				}
			}
			do {
				cout << "\nEnter role's ID to change role (100 - Customer, 101 - Librarian, 102 - Admin): ";
				cin >> inpRID;
				switch (inpRID) {
				case 100:
					temprole = Role("Customer", 100);
					valid_role = true;
					break;
				case 101:
					temprole = Role("Librarian", 101);
					valid_role = true;
					break;
				case 102:
					temprole = Role("Admin", 102);
					valid_role = true;
					break;
				default:
					cout << "\nInvalid data. Please try again.";
					valid_role = false;
				}
			} while (!valid_role);

			bool found = false;
			for (auto& libus : libusers) {
				if (
					libus.GetLibUserID() == inpUID &&
					libus.GetLibCard().GetLibID() == luser.GetLibCard().GetLibID()
					) {
					libus.GetLibCard().SetRole(temprole);
					SaveLibUsersToFile(libusers, "librarys_users.txt");
					cout << "\nRole updated successfully!\n";
					found = true;
					break;
				}
			}
			if (!found) {
				cout << "\nUser in this library not found!\n";
			}
			break;
		}

		case 3: {
			bool found = false;
			for (auto& lib : libs) {
				if (lib.GetID() == luser.GetLibCard().GetLibID()) {
					found = true;
					cout << "\nWhat do you want to change?";
					cout << "\n1. Library name";
					cout << "\n2. Library address";
					cout << "\nEnter your choice: ";
					int change_choice = SafeInput<int>("\nEnter your choice: ");
					cin.ignore();
					switch (change_choice) {
					case 1: {
						cout << "\nCurrent name: " << lib.GetName();
						cout << "\nEnter new library name: ";
						string newName;
						getline(cin, newName);
						lib.SetName(newName);
						SaveLibrariesToFile(libs, "libraries.txt");
						cout << "\nLibrary name updated successfully!";
						break;
					}
					case 2: {
						cout << "\nCurrent address: " << lib.GetAddress();
						cout << "\nEnter new library address: ";
						string newAddr;
						getline(cin, newAddr);
						lib.SetAddress(newAddr);
						SaveLibrariesToFile(libs, "libraries.txt");
						cout << "\nLibrary address updated successfully!";
						break;
					}
					default:
						cout << "\nInvalid option!";
						break;

					}
					break;
				}
			}
			if (!found) cout << "\nLibrary not found!";
			break;
		}

		default:
			cout << "\nInvalid option.";
			break;
		}
	}
}
void UserMenu(
	User& user1,
	bool& in_account,
	deque<User>&users,
	deque<LibraryUser>& libusers,
	deque<Library>& libs,
	deque<Book*>& books,
	deque<Order>& orders)
{
	while (in_account) {
		cout << "\nWhat do you want to do?";
		cout << "\n0. Log out";
		cout << "\n1. Become a library user";
		cout << "\n2. Log in to my library account";
		int acc_choice = SafeInput<int>("\nEnter your choice: ");

		switch (acc_choice) {
		case 0:
			cout << "\nLogged out.";
			in_account = false;
			break;

		case 1: {
			LibraryUser luser = BecomeLibUs(user1,books, libusers, libs);
			break;
		}

		case 2: {
			bool correct;
			bool rolevalid;
			LibraryCard tempLC;
			Role temprole;
			LibraryUser loglibuser;
			do {
				tempLC.ConsoleInput();
				do {
					temprole.ConsoleRead();
					rolevalid = temprole.ValidateRole();
					if (!rolevalid) {
						cout << "\nInvalid role, please try again: ";
					}
				} while (!rolevalid);
				tempLC.SetRole(temprole);
				correct = tempLC.ValidateID(libs);
				if (!correct) {
					cout << "\nInvalid library ID.Please try again.";
				}
			} while (!correct);
			loglibuser = LibraryUser(user1.GetUserId(), tempLC);
			if (LibraryUserExists(loglibuser, libusers)) {
				switch (loglibuser.GetLibCard().GetRole().GetId()) {
				case 100:
					CustomerFuncMenu(loglibuser, in_account, users, libusers, libs, books, orders);
					break;
				case 101:
					LibrarianFuncMenu(loglibuser, in_account, libs, books, orders);
					break;
				case 102:
					AdminFuncMenu(loglibuser, in_account, libusers, libs);
					break;
				}
			}
			else {
				cout << "\nSuch account does not exist, please register one.";
			}
			break;
		}
		default:
			cout << "\nInvalid option.";
			break;
		}
	}
}
void MainProgram(
	deque<User>& users,
	deque<Book*>& books,
	deque<Library>& libs,
	deque<LibraryUser>& libusers,
	deque<Order>& orders)
{
	bool running = true;

	while (running) {
		startmenu();
		int startchoice = SafeInput<int>("\nEnter your choice: ");

		switch (startchoice) {
		case 0:
			running = false;
			break;

		case 1: {
			int counter = 0;
			string mail, pass;
			bool in_account = false;
			User user1;
			do {
				cout << "\nEnter your email: ";
				cin >> mail;
				cout << "Enter your password: ";
				cin >> pass;
				user1 = Logining(counter, in_account, users, mail, pass);
				if (counter == 3) {
					cout << "\nYou entered wrong credentials 3 times.";
					break;
				}
			} while (counter < 3 && !in_account);

			if (in_account) {
				UserMenu(user1, in_account, users, libusers, libs, books, orders);
			}
			break;
		}
		case 2:
			Registration(users);
			break;

		default:
			cout << "\nInvalid choice. Try again.\n";
			break;
		}
	}
}


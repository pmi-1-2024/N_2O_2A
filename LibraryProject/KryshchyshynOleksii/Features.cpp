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


void SaveLibrariesToFile( deque<Library>& libraries, const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cout << "Error opening file for writing!\n";
		return;
	}

	outFile << libraries.size() << "\n";
	for ( auto& lib : libraries) {
		lib.PrintToFile(outFile);
	}

	outFile.close();
}

void SaveOrdersToFile(deque<Order>& orders, const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cout << "Error opening file for writing!\n";
		return;
	}

	outFile << orders.size() << "\n";
	for (auto& ord : orders) {
		outFile<<ord;
	}

	outFile.close();
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




void AddBook(const LibraryBook& book, deque<Library>& libs, const string& filename, Library&lib)
{
	lib.GetBooks().push_back(book);
	SaveLibrariesToFile(libs, filename);
	cout << "Book added to library and file updated.\n";
}

void Registration(deque<User>& users)
{
	User us;
	do {
		us.ConsoleInput();
	} while (us.ValidateEmail() != true);
	users.push_back(us);
	cout << "\nYour account is registered!";
	AddToFile("users.txt", us);
}
bool LibraryUserExists(const LibraryUser& target, const deque<LibraryUser>& libusers) {
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
		else { cout << "\nYou entered an incorrect email or password, please try again"; }
		counter++;
	}
	return User();
}
LibraryCard CreateLibCard(deque<Library>& libs)
{
	LibraryCard lc;
	do {
		lc.ConsoleInput();
		if (lc.ValidateID(libs) == false) {
			cout << "\nInvalid library id, please try again.";
		}
	} while (lc.ValidateID(libs) == false);
	cout << "\nYour library card has been successfully created!";
	return lc;
}
LibraryUser BeacomeLibUs(const User& us,deque<LibraryUser>&libusers, deque<Library>& libs)
{
	bool access = true;
	LibraryUser libus;
		do {
			string id;
			do {
				cout << "\nEnter your ID:";
				cin >> id;
				if (id != us.GetUserId()) {
					cout << "\ninvalid id!";
				}
			} while (id != us.GetUserId());
			LibraryCard lc = CreateLibCard(libs);
			libus= LibraryUser(id, lc);
			if (LibraryUserExists(libus, libusers)) {
				cout << "\nYou are already registered in this library, try another one.";
				access = false;
			}
		} while (access == false);
			cout << "You have successfully become a client of the library: " << libus.GetLibCard().GetLibID();
		for (auto& lib : libs) {
			if (libus.GetLibCard().GetLibID() == lib.GetID()) {
				cout << lib.GetName();
			}
		}
	libusers.push_back(libus);
	AddToFile("librarys_users.txt", libus);
	return libus;
}

void PlaceAnOrder( LibraryUser& libuse, deque<Order>& orders, deque<Library>& libs)
{
	Order od;
	bool accesstoplace = false;
	od.ConsoleInput();
	for (auto& libbok : libuse.getLibrary(libs).GetBooks()) {
			if (od.getBookID() == libbok.GetID() && od.getUserID() == libuse.GetLibUserID()) {
				accesstoplace = true;
				cout << "\nYou have successfully checked out a book from the library!";
				orders.push_back(od);
				AddToFile("orders.txt", od);
				break;
			}
	}
	if (!accesstoplace) cout << "\nError: book ID not found in your library or user ID mismatch.";
}

void startmenu()
{
	cout << "\nWelcome!";
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit";
	cout << "\n1. Log in";
	cout << "\n2. Sign up";
	cout << "\nEnter your choice: ";
}

void UpdateBookInfo(Library& lib, const string& filename, deque<Library>&libs)
{
	int bookID;
	cout << "\nEnter the ID of the book you want to update: ";
	cin >> bookID;

	
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

void RemoveOrderById(const string& filename, LibraryUser& libusr, deque<Order>& orders)
{
	string libID = libusr.GetLibCard().GetLibID();

	cout << "\nYour orders in this library:\n";
	bool foundAny = false;

	ShowOrders(orders, libusr);

	if (!foundAny) {
		cout << "You have no orders in this library.\n";
		return;
	}

	int orderIdToDelete;
	cout << "Enter the ID of the order to delete: ";
	cin >> orderIdToDelete;

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

void ShowOrders(deque<Order>& orders, LibraryUser& libusr)
{
	for (const auto& order : orders) {
		if (order.getLibId() == libusr.GetLibCard().GetLibID()) {
			order.ConsolePrint();
			cout << "-------------------------\n";
		}
	}
}


void CustomerMenu()
{
	cout << "\nWhat do you want to do?";
	cout << "\n0. Exit";
	cout << "\n1. Return to login menu";
	cout << "\n2. View libraries where I am registered";
	cout << "\n3.View books in my library";
	cout << "\n4. Place an order for a book";
	cout << "\n5. Become a user of another library";
	cout << "\nEnter your choice: ";
}

/////
void LibraryMenu()
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
	cout << "\n\nEnter your choice: ";
}

void BookBrowsingMenu(int& bookid,LibraryUser& libuser,deque<Library>&libs, deque<Book*>& books)
{
	bool ifprint = false;
			for (auto& libbook : libuser.getLibrary(libs).GetBooks()) {
				for (Book* b : books) {
					if (libbook.GetID() == bookid && b->getID() == bookid) {
						b->Consoleprint();
						ifprint = true;
					}
				}
			}
	if (ifprint == false) {
		cout << "\nThere is no book with this ID!";
	}
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
		int lib_choice;
		CustomerMenu();
		cin >> lib_choice;

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

		case 2:
			cout << "\nLibraries where I am registered:\n";
			for (auto& libus : libusers) {
				if (libus.GetLibUserID() == luser.GetLibUserID()) {
					libus.GetLibCard().ConsolePrint();
					cout << "\n";
				}
			}
			break;

		case 3:
			cout << "\n";
			luser.getLibrary(libs).ShowBooks();
			cout << "\nWould you like more info about a book?\n1. No\n2. Yes\n";
			int choice;
			cin >> choice;
			if (choice == 2) {
				int bookid;
				cout << "\nEnter book ID: ";
				cin >> bookid;
				BookBrowsingMenu(bookid, luser, libs, books);
			}
			break;

		case 4:
			PlaceAnOrder(luser, orders, libs);
			break;

		case 5: {
			LibraryUser new_luser = BeacomeLibUs(luser.getUser(users), libusers, libs);
			luser = new_luser;
			break;
		}

		default:
			cout << "\nInvalid option.";
			break;
		}
	}
}


//////
void LibraryUserMenu(
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
		int lib_choice;
		CustomerMenu();
		cin >> lib_choice;

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

		case 2:
			luser.getLibrary(libs).ShowBooks();
			
			break;

		case 3:
			LibraryBook tempBook;
			tempBook.ConsoleInput(books);
			AddBook(tempBook, libs, "libraries.txt", luser.getLibrary(libs));
			break;

		case 4:
			UpdateBookInfo(luser.getLibrary(libs), "libraries.txt", libs);

			break;

		case 5: {
			luser.getLibrary(libs).ShowBooks();
			cout << "please enter id of book to remove: ";
			int id;
			cin >> id;
			RemoveBookByID(id, "libraeies.txt", luser.getLibrary(libs), libs);
			break;
		}
		case 6: {
			ShowOrders(orders, luser);
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
		int acc_choice;
		cout << "\nWhat do you want to do?";
		cout << "\n0. Log out";
		cout << "\n1. Become a library user";
		cout << "\n2. Log in to my library account";
		cout << "\nEnter your choice: ";
		cin >> acc_choice;

		switch (acc_choice) {
		case 0:
			cout << "\nLogged out.";
			in_account = false;
			break;

		case 1: {
			LibraryUser luser = BeacomeLibUs(user1, libusers, libs);
			CustomerFuncMenu(luser, in_account,users, libusers, libs, books, orders);
			break;
		}

		case 2: {
			bool libaccess = false;
			LibraryUser loglibuser;
			cout << "\nEnter your information";
			do {
				loglibuser.ConsoleInput();
				if (loglibuser.GetLibUserID() != user1.GetUserId() || loglibuser.GetLibCard().ValidateID(libs) == false){
					cout<<"\nInvalid data(user id ot lib id, please try again";
				}
			} while (loglibuser.GetLibUserID() != user1.GetUserId() || loglibuser.GetLibCard().ValidateID(libs) == false);
			if (LibraryUserExists(loglibuser, libusers)) {
				libaccess = true;
			}
			if (libaccess) {
				CustomerFuncMenu(loglibuser, in_account,users, libusers, libs, books, orders);
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
		int startchoice;
		startmenu();
		cin >> startchoice;

		switch (startchoice) {
		case 0:
			running = false;
			break;

		case 1: {
			int counter = 0;
			string mail, pass;
			cout << "\nEnter your email: ";
			cin >> mail;
			cout << "\nEnter your password: ";
			cin >> pass;

			bool in_account = false;
			User user1;
			do {
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


#include "Order.h"
#include <stdexcept> 
#include <limits>    

Order::Order() : id(0), bookID(0), libId(""), userID(""), startDay("") {}

Order::Order(int i, int bid, string lbId, string uid, string sd)
    : id(i), bookID(bid), libId(lbId), userID(uid), startDay(sd) {}

int Order::getId() const { return id; }

int Order::getBookID() const { return bookID; }

int Order::getOrderId() const { return id; }

string Order::getUserID() const { return userID; }

string Order::getLibId() const { return libId; }

void Order::SetUserID(string userid)
{
    if (userid.empty()) {
        throw invalid_argument("User ID cannot be empty");
    }
    userID = userid;
}

void Order::SetLibID(string libID)
{
    if (libID.empty()) {
        throw invalid_argument("Library ID cannot be empty");
    }
    libId = libID;
}

void Order::ConsolePrint() const
{
    cout << "\nOrder ID: " << id << "; Library Id: " << libId << ", Book ID: " << bookID;
    cout << "\nUser ID: " << userID << ", Start Date: " << startDay;
}

void Order::ConsoleInput()
{
    cout << "\nEnter Order ID: ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid Order ID input");
    }
    cout << "\nEnter Book ID: ";
    cin >> bookID;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid Book ID input");
    }
    cin.ignore();
    cout << "\nEnter Start Date: ";
    getline(cin, startDay);
    if (startDay.empty()) {
        throw invalid_argument("Start date cannot be empty");
    }
}

istream& operator>>(istream& in, Order& o)
{
    in >> o.id >> o.bookID >> o.libId >> o.userID, in.ignore(), getline(in, o.startDay, ';');
    return in;
}

ostream& operator<<(ostream& out, const Order& o)
{
    out << "\n" << o.id << " " << o.bookID << " " << o.libId << " " << o.userID << " " << o.startDay << ";";
    return out;
}

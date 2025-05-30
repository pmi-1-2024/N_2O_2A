#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <string>
using namespace std;
class Order
{
private:
    int id;
    int bookID;
    string libId;
    string userID;
    string startDay;
public:
    Order();
    Order(int id, int bid, string lbId, string uid, string sd);
    int getId() const;
    int getBookID() const;
    int getOrderId() const;
    string getUserID() const;
    string getLibId() const;
    void SetUserID(string userid);
    void SetLibID(string libID);
    void ConsolePrint()const;
    void ConsoleInput();
    friend istream& operator>>(istream& in, Order& o);
    friend ostream& operator<<(ostream& out, const Order& o);
};
#endif


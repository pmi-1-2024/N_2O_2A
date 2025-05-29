#ifndef ROLE_H
#define ROLE_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Role {
private:
    string name = "Customer";
    int id = 100;
public:
    Role();
    Role(string name, int id);
    string GetName() const;
    int GetId() const;
    void SetName(string name);
    void SetId(int id);
    void ConsolePrint() const;
    void ConsoleRead();
    bool ValidateRole();
    bool operator==(const Role& other) const;
    friend ostream& operator<<(ostream& out, const Role& role);
    friend istream& operator>>(istream& in, Role& role);
};

#endif

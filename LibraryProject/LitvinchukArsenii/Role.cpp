#include "Role.h"

bool Role::ValidateRole()
{
    if ((id == 100 && name == "Customer") || (id == 101 && name == "Librarian") || (id == 102 && name == "Administrator")) {
        return true;
    }
    cout << "\nThis role does not exist!";
    return false;
}

Role::Role() : name(""), id(0) {}

Role::Role(string name, int id) : name(name), id(id) {}

string Role::GetName() const {
    return name;
}
int Role::GetId() const {
    return id;
}

void Role::SetName(string name) {
    this->name = name;
}
void Role::SetId(int id) {
    this->id = id;
}

void Role::ConsolePrint() const {
    cout << id << ": " << name;
}
void Role::ConsoleRead() {
    cout << "\nEnter role ID: ";
    cin >> id;
    cin.ignore();
    cout << "\nEnter role name: ";
    getline(cin, name);
}

ostream& operator<<(ostream& out, const Role& role) {
    out << role.id << " " << role.name << ";";
    return out;
}
istream& operator>>(istream& in, Role& role) {
    in >> role.id, in.ignore(), getline(in, role.name, ';');
    return in;
}

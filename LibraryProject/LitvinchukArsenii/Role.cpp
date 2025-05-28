#include "Role.h"

bool Role::ValidateRole()
{
    if ((id == 100 && name == "Customer") || (id == 101 && name == "Librarian") || (id == 102 && name == "Admin")) {
        return true;
    }
    cout << "\nThis role does not exist!";
    return false;
}

bool Role::operator==(const Role& other) const
{
    return name == other.name && id == other.id;
}

Role::Role() : name(""), id() {}

Role::Role(string name, int id) : name(name), id(id) {}

string Role::GetName() const {
    return name;
}
int Role::GetId() const {
    return id;
}

void Role::SetName(string name) {
    if (name.empty()) throw invalid_argument("Role name cannot be empty");
    this->name = name;
}

void Role::SetId(int id) {
    if (id != 100 && id != 101 && id != 102) throw invalid_argument("Invalid Role ID");
    this->id = id;
}


void Role::ConsolePrint() const {
    cout << id << ": " << name;
}
void Role::ConsoleRead() {
    cout << "\nEnter role ID(100-Customer,101-Librarian,102-Admin): ";
    cin >> id;
    cout << "\nEnter role name: ";
    cin >> name;
}

ostream& operator<<(ostream& out, const Role& role) {
    out << role.id << " " << role.name;
    return out;
}
istream& operator>>(istream& in, Role& role) {
    in >> role.id >> role.name;
    return in;
}
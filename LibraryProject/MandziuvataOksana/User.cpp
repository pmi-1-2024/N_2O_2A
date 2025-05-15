#include "User.h"
#include <stdexcept>
#include <algorithm>

User::User() : firstName(""), lastName(""), userId(""), email(""), password("") {}

User::User(const string& first, const string& last, const string& id,
    const string& mail, const string& pass) : firstName(first), lastName(last), userId(id), email(mail), password(pass) {}


bool User::ValidateEmail() {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    if (atPos == string::npos || dotPos == string::npos || dotPos <= atPos + 1) {
        cout << "\nInvalid email format!";
        return false;
    }
    return true;
}

string User::GetName() const {
    return firstName;
}

string User::GetLastName() const
{
    return lastName;
}

string User::GetEmail() const {
    return email;
}

string User::GetUserId() const {
    return userId;
}

void User::ConsolePrint() const
{
    cout << "\nUser: " << userId << ": " << firstName << " " << lastName << ", " << email;
}

void User::ConsoleInput()
{
    cout << "\nEnter ID: ";
    cin >> userId;
    cout << "\nEnter name: ";
    cin >> firstName;
    cin.ignore();
    cout << "\nEnter last name: ";
    getline(cin, lastName);
    cout << "\nEnter email: ";
    cin >> email;
    cout << "\nEnter password: ";
    cin >> password;
}

bool User::CheckPassword(const string& inputPassword) const {
    return password == inputPassword;
}

void User::SetPassword(const string& newPassword) {
    password = newPassword;
}

void User::SetEmail(const string& newEmail) {
    ValidateEmail();
    email = newEmail;
}

istream& operator>>(istream& is, User& u)
{
    is >> u.userId >> u.firstName, is.ignore(), getline(is, u.lastName, ','), is >> u.email >> u.password;
    return is;
}

ostream& operator<<(ostream& os, const User& u)
{
    os << u.userId << " " << u.firstName << " " << u.lastName << ", " << u.email << " " << u.password;
    return os;
}


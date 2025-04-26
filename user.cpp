// #include "consoleapp.cpp"
#include "user.h"

// extern ConsoleApp app;

User::User(string name, string login, string password) {
// TODO encrypt password
    this->login = login;
    this->name = name;
    this->salted_password = password;
    // this->salted_password = app.encrypt(password);
}

// User::virtual void main() 

void User::see_tickets() {

}

void User::buy_ticket() {

}

void User::check_booked_tickets() {

}

void User::cancel_ticket() {

}

string User::serialize() {
    string s = "{\"login\": \"" + this->login + "\", \"salted_password\": \"" + this->salted_password + "\", \"name\": \n" + this->name + "\n}";
    // todo: add tickets
    return s;
}

User::User(string data) {
    int start = data.find_first_of('{');
    for (int i = start; i < data.size(); i++) {
        int code = data[i];
        
    }
}

bool User::check_credentials(string login, string salted_password) {
    return (login == this->login && salted_password == this->salted_password);
} 

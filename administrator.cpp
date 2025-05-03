#include "administrator.h"
#include "consoleapp.h"
#include "jsonserializer.h"
#include "jsondeserializer.h"

Administrator::Administrator(string name, string login, string password): User(name, login, password){}

extern ConsoleApp *app;

void Administrator::manage_users() {
    vector<User*> users = app->users;
    // TODO: user table
    for (int i = 0; i < users.size(); i++) {
        User *user = users[i];
        cout << utils::centered(to_string(i + 1) + ".", 5) << user->name << endl;
    }
    int choice = utils::getInt(0, users.size(), "Enter 0 to leave, user index 1 - " + to_string(users.size() - 1) + 
        ", or " + to_string(users.size()) + " to create new user: ");
    if (choice == 0) {
        return;
    }
    if (choice == users.size()) {
        cout << "Creating a new user" << endl;
        string name = utils::getString("Enter new user's name:");
        string login = utils::getString("Enter new user's login:");
        string password = utils::getString("Enter new user's password:");
        int is_admin = utils::getInt(0, 1, "Enter 1 if user is adminstrator, otherwise 0");
        if (is_admin) {
            Administrator *a = new Administrator(name, login, password);
            app->users.push_back(a);
        } else {
            User *u = new User(name, login, password);
            app->users.push_back(u);
        }
        cout << "Successfully created " << (is_admin? "administrator ": "user ") << name << endl;
        return this->manage_users();
    }
    // TODO: manage user
}

void Administrator::manage_buses() {

}

string Administrator::serialize() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_string("login", this->login);
    serializer.serialize_string("salted_password", this->salted_password);
    serializer.serialize_string("name", this->name);
    serializer.serialize_vector<Ticket>("tickets", this->tickets);
    serializer.serialize_int("is_admin", 1);
    cout << serializer.get_result();
    return serializer.get_result();
}

Administrator::Administrator(string json): User(json) {}

#include "administrator.h"
#include "consoleapp.h"
#include "jsonserializer.h"
#include "jsondeserializer.h"

Administrator::Administrator(string name, string login, string password): User(name, login, password){}

extern ConsoleApp *app;

void Administrator::manage_users() {
    vector<User*> &users = app->users;
    // TODO: user table
    for (int i = 0; i < users.size(); i++) {
        User *user = users[i];
        cout << utils::centered(to_string(i + 1) + ".", 5) << user->name << endl;
    }
    int choice = utils::getInt(0, users.size(), "Enter 0 to leave, user index 1 - " + to_string(users.size()) + 
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
    choice--;
    while (true) {
        cout << "User info: " << endl;
        cout << "1. Name: " << users[choice]->name << endl;
        cout << "2. Login: " << users[choice]->login << endl;
        cout << "3. Password: *hidden*" << endl;
        cout << "4. Role: " << ((users[choice]->is_admin() == 1)? "administrator": "user") << endl;
        // TODO: (questionable) add ticket managing
        // TODO: (questionable) add account deleting
        int k = utils::getInt(0, 4, "Enter field number to edit or 0 to return: ");
        if (k == 0) {
            return this->manage_users();
        }
        if (k == 4) {
            if (users[choice] == this) {
                cout << "Unable to change own role " << endl;
            } else {
                if (users[choice]->is_admin() == 0) {
                    Administrator *a = new Administrator(users[choice]->serialize());
                    User *u = users[choice];
                    users[choice] = a;
                    delete u;
                    cout << "users[choice] = " << users[choice] << endl;
                } else {
                    User *u = new User(users[choice]->serialize());
                    User *a = users[choice];
                    users[choice] = u;
                    delete a;
                }
            }
        } else {
            string val = utils::getString("Enter new value");
            switch (k) {
                case 1: {
                    users[choice]->name = val;
                    cout << "Successfully changed user's name" << endl;
                    break;
                }
                case 2: {
                    users[choice]->login = val;
                    cout << "Successfully changed user's login" << endl;
                    break;
                }
                case 3: {
                    users[choice]->salted_password = utils::encrypt(val);
                    cout << "Successfully changed user's password" << endl;
                    break;
                }
            }
        }
    }
}

void Administrator::manage_buses() {

}

Administrator::Administrator(string json): User(json) {}

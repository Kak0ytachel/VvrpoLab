#include <string>
#include <iostream>
#include "user.h"
#pragma once

class Administrator: public User {
public: 
    Administrator(string name, string login, string password);

    void manage_users();

    void manage_buses();

    virtual void main() {
        cout << "Logged in as administrator " << this->name << endl;
        bool exitFlag = false;
        while (!exitFlag) {
            cout << "Menu: \n1. Browse bus routes\n2. View booked tickets\n3. Manage users\n4. Log out" << endl;
            int e = utils::getInt(1, 4, "Choose menu option: ");
            switch (e) {
                case 1: {
                    this->manage_buses();
                    break;
                }
                case 2: {
                    this->check_booked_tickets();
                    break;
                }
                case 3: {
                    this->manage_users();
                    break;
                }
                case 4: {
                    cout << "Logging out..." << endl;
                    exitFlag = true;
                    break;
                }
            }
        }
    }

    virtual bool is_admin() {
        return true;
    }

    Administrator(string json);
};

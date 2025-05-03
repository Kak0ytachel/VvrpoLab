#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
#pragma once

using namespace std;

class Ticket;

class User {
public:
    string login;
    string salted_password;
    string name;
    vector<Ticket*> tickets;
    User(string name, string login, string password);

    virtual void main() {
        cout << "Logged in as user " << this->name << endl;
        bool exitFlag = false;
        while (!exitFlag) {
            cout << "Menu: \n1. Browse bus routes\n2. View booked tickets\n3. Log out" << endl;
            int e = utils::getInt(1, 3, "Choose menu option: ");
            switch (e) {
                case 1: {
                    this->see_tickets();
                    break;
                }
                case 2: {
                    this->check_booked_tickets();
                    break;
                }
                case 3: {
                    cout << "Logging out..." << endl;
                    exitFlag = true;
                    break;
                }
            }
        }
    }

    void see_tickets();

    void check_booked_tickets();

    void buy_ticket(BusRoute *bus);

    string serialize();

    User(string json);

    virtual bool is_admin() {
        return false;
    }

    bool check_credentials(string login, string salted_password);
};
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
#pragma once

using namespace std;

class Ticket;

class User {
    string login;
    string salted_password;
    string name;
    vector<Ticket> tickets;
public:
    User(string name, string login, string password);

    virtual void main() {
        cout << "Logged in as user " << this->login << endl;
        bool exitFlag = false;
        while (!exitFlag) {
            cout << "Menu: \n1. View all tickets\n2. Buy ticket\n3. View booked tickets\n4. Cancel ticket\n5. Log out" << endl;
            int e = utils::getInt(1, 3, "Choose menu option");
            switch (e) {
                case 1: {
                    this->see_tickets();
                    break;
                }
                case 2: {
                    this->buy_ticket();
                    break;
                }
                case 3: {
                    this->check_booked_tickets();
                    break;
                }
                case 4: {
                    this->cancel_ticket();
                    break;
                }
                case 5: {
                    cout << "Logging out..." << endl;
                    exitFlag = true;
                    break;
                }
            }
        }
    }

    void see_tickets();

    void buy_ticket();

    void check_booked_tickets();

    void cancel_ticket();

    string serialize();

    User(string data);

    virtual bool is_admin() {
        return false;
    }

    bool check_credentials(string login, string salted_password);
};
#include <iomanip>
#include "user.h"
#include "utils.h"
#include "consoleapp.h"
#include "busroute.h"
#pragma once

extern ConsoleApp *app;

User::User(string name, string login, string password) {
// TODO encrypt password
    this->login = login;
    this->name = name;
    this->salted_password = utils::encrypt(password);
}


void User::see_tickets() {
    cout << "See tickets";
    cout << endl;
    cout << " No. |" << utils::centered("Origin", 12) << "|" << utils::centered("Departure", 12) << "|" << utils::centered("Destination", 12) << "|" << 
        utils::centered("Arrival", 12) << "|" << utils::centered("Tickets", 10) << endl;
    vector<BusRoute*> buses = app->get_all_buses();
    for (int i = 0; i < buses.size(); i++) {
        BusRoute *bus = buses[i];
        cout << utils::centered(to_string(i+1) + ".", 5) << "|" << utils::centered(bus->origin, 12) << "|" << utils::centered(bus->departure.format_t(), 12) 
            << "|" << utils::centered(bus->destination, 12) << "|" << utils::centered(bus->arrival.format_t(), 12) << "|" <<
            utils::centered(to_string(bus->ticketsLeft), 10) << endl;
    }
    int choice = utils::getInt(0, buses.size(), "Enter number of ticket for details or 0 to exit");
    if (choice == 0) {
        return;
    }
    BusRoute *bus = buses[choice-1];
    while (true) {
        cout << "Details: " << endl;
        cout << "Origin: " << bus->origin << endl;
        cout << "Departure: " << bus->departure.format_dt() << endl;
        cout << "Destination: " << bus->destination << endl;
        cout << "Arrival: " << bus->arrival.format_dt() << endl;
        cout << "Tickets left: " << bus->ticketsLeft << endl;
        cout << "Options: \n1. Book ticket(s)\n2. Back to tickets list\n3. Exit to menu\n";
        int option = utils::getInt(1, 3, "Choose option");
        switch(option) {
            case (1): {
            int quantity = utils::getInt(0, bus->ticketsLeft, "Enter quantity of tickets to book");
            if (quantity == 0) {
                cout << "Cancelled booking" << endl;
            }
            this->tickets.push_back(bus->buy_ticket(quantity));
            cout << "Booked " << quantity << " tickets" << endl;
            break;
        } 
        case (2): {
            this->see_tickets();
            return;
        }
        case (3): {
            return;
        }}
    }

}

void User::buy_ticket() {
    cout << "Buy tickets";
}

void User::check_booked_tickets() {
    cout << "Checked booked tickets";
}

void User::cancel_ticket() {
    cout << "Cancel tickets";
}

string User::serialize() {
    string s = "{\"login\": \"" + this->login + "\", \"salted_password\": \"" + this->salted_password + "\", \"name\": \n" + this->name + "\n}";
    // todo: rewrite
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

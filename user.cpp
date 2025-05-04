#include <iomanip>
#include "user.h"
#include "utils.h"
#include "consoleapp.h"
#include "busroute.h"
#include "jsonserializer.h"
#pragma once

extern ConsoleApp *app;

User::User(string name, string login, string password) {
// TODO encrypt password
    this->login = login;
    this->name = name;
    this->salted_password = utils::encrypt(password);
}


void User::see_tickets() {
    cout << "Browsing bus routes..." << endl;
    vector<BusRoute*> buses = app->get_all_buses();
    utils::showBuses(buses);
    int choice = utils::getInt(0, buses.size(), "Enter number of ticket for details or 0 to exit: ");
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
        cout << "Price per ticket: " << bus->price << endl;
        cout << "Options: \n1. Book ticket(s)\n2. Back to tickets list\n3. Exit to menu\n";
        int option = utils::getInt(1, 3, "Choose option: ");
        switch(option) {
            case (1): {
                this->buy_ticket(bus);
                break;
            } 
            case (2): {
                this->see_tickets();
                return;
            }
            case (3): {
                return;
            }
        }
    }
}

void User::buy_ticket(BusRoute *bus) {
    int quantity = utils::getInt(0, bus->ticketsLeft, "Enter quantity of tickets to book: ");
    if (quantity == 0) {
        cout << "Cancelled booking" << endl;
    }
    Ticket *new_ticket = bus->buy_ticket(quantity);
    for (int i = 0; i < this->tickets.size(); i++) {
        if (this->tickets[i]->routeId == new_ticket->routeId && this->tickets[i]->is_canceled == 0) {
            this->tickets[i]->quantity += new_ticket->quantity;
            delete new_ticket;
            new_ticket = nullptr;
            break;
        }
    }
    if (new_ticket != nullptr) {
        this->tickets.push_back(new_ticket);
    }
    cout << "Booked " << quantity << " tickets" << endl;
}

void User::check_booked_tickets() {
    cout << "Checked booked tickets";
    cout << endl;
    utils::showTickets(this->tickets);
    int choice = utils::getInt(0, this->tickets.size(), "Enter number of ticket for details or 0 to exit: ");
    if (choice == 0) {
        return;
    }
    BusRoute *bus = this->tickets[choice-1]->get_bus();
    while (true) {
        cout << "Details: " << endl;
        cout << "Origin: " << bus->origin << endl;
        cout << "Departure: " << bus->departure.format_dt() << endl;
        cout << "Destination: " << bus->destination << endl;
        cout << "Arrival: " << bus->arrival.format_dt() << endl;
        cout << "Tickets booked: " << tickets[choice-1]->quantity << endl;
        cout << "Options: \n1. Cancel ticket(s)\n2. Back to tickets list\n3. Exit to menu\n";
        int option = utils::getInt(1, 3, "Choose option: ");
        switch(option) {
            case (1): {
                tickets[choice-1]->cancel();
                this->tickets.erase(this->tickets.begin() + choice - 1);
                cout << "Cancelled tickets" << endl;
            } 
            case (2): {
                this->check_booked_tickets();
                return;
            }
            case (3): {
                return;
            }
        }
    }
}

bool User::check_credentials(string login, string salted_password) {
    return (login == this->login && salted_password == this->salted_password);
} 

string User::serialize() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_string("login", this->login);
    serializer.serialize_string("salted_password", this->salted_password);
    serializer.serialize_string("name", this->name);
    serializer.serialize_vector<Ticket>("tickets", this->tickets);
    serializer.serialize_int("is_admin", this->is_admin());
    // cout << serializer.get_result() << endl;
    return serializer.get_result();
}

User::User(string json) {
    // cout << "Deeserializing User" << endl;
    JsonDeserializer deserializer = JsonDeserializer(json);
    this->login = deserializer.deserialize_string("login");
    this->name = deserializer.deserialize_string("name");
    this->salted_password = deserializer.deserialize_string("salted_password");
    this->tickets = deserializer.deserialize_vector<Ticket>("tickets");
}
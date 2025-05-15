#include <iomanip>
#include "user.h"
#include "utils.h"
#include "consoleapp.h"
#include "busroute.h"
#include "jsonserializer.h"
#pragma once

extern ConsoleApp *app;

User::User(string name, string login, string password) {
    this->login = login;
    this->name = name;
    this->salted_password = utils::encrypt(password);
}


void User::see_tickets() {
    cout << "Browsing bus routes..." << endl;
    // TODO: (questionable) add search & sorting
    bool isSortingDone = false;
    vector<BusRoute*> buses = app->get_all_buses();
    while (!isSortingDone){
        utils::showBuses(buses);
        int opt = utils::getInt(1, 4, "Options: \n1. View route\n2. Apply filter\n3. Sort routes\n4. Exit\n");
        switch (opt) {
            case 1: {
                isSortingDone = true;
                break;

            }
            case 2: {
                int field = utils::getInt(1, 4, "Choose field to filter: \n1. Origin\n2. Destination\n3. Price\n4. Reset filters\n");
                switch (field) {
                    case 1: {
                        string target = utils::getString("Enter origin to look for");
                        vector<BusRoute*> temp;
                        for (BusRoute *bus: buses) {
                            string s1 = utils::to_lower(bus->origin);
                            string s2 = utils::to_lower(target);
                            if (s1.find(s2) != string::npos || s2.find(s1) != string::npos) {
                                temp.push_back(bus);
                            }
                        }
                        if (temp.size() == 0) {
                            cout << "No routes found, revoking filter" << endl;
                        } else {
                            buses.clear();
                            buses.assign(temp.begin(), temp.end());
                            cout << "Successfully applied filter" << endl;
                        }
                        break;
                    }
                    case 2: {
                        string target = utils::getString("Enter destination to look for");
                        vector<BusRoute*> temp;
                        for (BusRoute *bus: buses) {
                            string s1 = utils::to_lower(bus->destination);
                            string s2 = utils::to_lower(target);
                            if (s1.find(s2) != string::npos || s2.find(s1) != string::npos) {
                                temp.push_back(bus);
                            }
                        }
                        if (temp.size() == 0) {
                            cout << "No routes found, revoking filter" << endl;
                        } else {
                            buses.clear();
                            buses.assign(temp.begin(), temp.end());
                            cout << "Successfully applied filter" << endl;
                        }
                        break;
                    }
                    case 3: {
                        double minPrice = utils::getDouble("Enter minimal price: ", 2);
                        double maxPrice = utils::getDouble("Enter maximal price: ", 2);
                        vector<BusRoute*> temp;
                        for (BusRoute *bus: buses) {
                            if (bus->price >= minPrice && bus->price <= maxPrice) {
                                temp.push_back(bus);
                            }
                        }
                        if (temp.size() == 0) {
                            cout << "No routes found, revoking filter" << endl;
                        } else {
                            buses.clear();
                            buses.assign(temp.begin(), temp.end());
                            cout << "Successfully applied filter" << endl;
                        }
                        break;
                    }
                    case 4: {
                        buses = app->get_all_buses();
                        cout << "Successfully removed filters" <<endl;
                        break;
                    }
                }
                break;
            }
            case 3: {

                break;
            }

            case 4: {
                return;
            }
        }
    }
    int choice = utils::getInt(0, buses.size(), "Enter number of route for details or 0 to exit: ");
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
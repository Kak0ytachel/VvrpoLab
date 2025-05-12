#include "administrator.h"
#include "consoleapp.h"
#include "jsonserializer.h"
#include "jsondeserializer.h"
#include "busroute.h"

Administrator::Administrator(string name, string login, string password): User(name, login, password){}

extern ConsoleApp *app;

void Administrator::manage_users() { 
    vector<User*> &users = app->users;
    // TODO: (questionable) user table
    for (int i = 0; i < users.size(); i++) {
        User *user = users[i];
        cout << utils::centered(to_string(i + 1) + ".", 5) << user->name << endl;
    }
    int choice = utils::getInt(0, users.size(), "Enter 0 to leave, user index 1 - " + to_string(users.size()) + 
        ", or " + to_string(users.size()+1) + " to create new user: ");
    if (choice == 0) {
        return;
    }
    if (choice == users.size() + 1) {
        cout << "Creating a new user" << endl;
        string name = utils::getString("Enter new user's name:");
        string login = utils::getString("Enter new user's login:");
        string password = utils::getString("Enter new user's password:");
        int is_admin = utils::getInt(0, 1, "Enter 1 if user is adminstrator, otherwise 0");
        if (is_admin) {
            Administrator *a = new Administrator(name, login, password);
            users.push_back(a);
        } else {
            User *u = new User(name, login, password);
            users.push_back(u);
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
    cout << "Browsing bus routes..." << endl;
    vector<BusRoute*> buses = app->get_all_buses();
    utils::showBuses(buses);
    int choice = utils::getInt(0, buses.size()+1, "Enter number of bus route for details, " + to_string(buses.size() + 1) 
        + " to create a new one or 0 to exit: ");
    if (choice == 0) {
        return;
    }
    if (choice == buses.size() + 1) {
        string origin = utils::getString("Enter origin: ");
        Datetime departure = utils::getDate("Enter departure time: ");
        string destination = utils::getString("Enter destination: ");
        Datetime arrival = utils::getDate("Enter arrival time: ");
        int tickets = utils::getInt(0, 9999, "Enter tickets quanity: ");
        double price = utils::getDouble("Enter ticket price: ", 2);
        BusRoute *new_route = new BusRoute(origin, destination, departure, arrival, tickets, price);
        cout << "Successfully created a new bus route" << endl;
        return this->manage_buses();
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
        cout << "Options: \n1. Book ticket(s)\n2. Edit bus route\n3. Back to tickets list\n4. Exit to menu\n";
        int option = utils::getInt(1, 4, "Choose option: ");
        switch(option) {
            case 1: {
                this->buy_ticket(bus);
                break;
            } 
            case 2: {
                cout << "Details: " << endl;
                cout << "1. Origin: " << bus->origin << endl;
                cout << "2. Departure: " << bus->departure.format_dt() << endl;
                cout << "3. Destination: " << bus->destination << endl;
                cout << "4. Arrival: " << bus->arrival.format_dt() << endl;
                cout << "5. Tickets left: " << bus->ticketsLeft << endl;
                cout << "6. Price per ticket: " << bus->price << endl;
                int field = utils::getInt(1, 6, "Enter number of the field to edit or 0 to cancel: ");
                switch (field) {
                    case 0: {
                        cout << "Cancelled editing" << endl;
                        continue;
                    }
                    case 1: {
                        string origin = utils::getString("Enter new origin: ");
                        bus->origin = origin;
                        cout << "Succesfully changed origin to " << origin;
                        break;
                    }
                    case 2: {
                        Datetime departure = utils::getDate("Enter new departure time: ");
                        bus->departure = departure;
                        cout << "Succesfully changed departure time to " << departure.format_dt();
                        break;
                    }
                    case 3: {
                        string destination = utils::getString("Enter new destination: ");
                        bus->destination = destination;
                        cout << "Succesfully changed destination to " << destination;
                        break;
                    }
                    case 4: {
                        Datetime arrival = utils::getDate("Enter new arrival time: ");
                        bus->arrival = arrival;
                        cout << "Succesfully changed arrival time to " << arrival.format_dt();
                        break;
                    }
                    case 5: {
                        int tickets = utils::getInt(0, 9999, "Enter new tickets quanity: ");
                        bus->seatsTotal = bus->seatsTotal - bus->ticketsLeft + tickets;
                        bus->ticketsLeft = tickets;
                        cout << "Succesfully changed tickets quantity to " << tickets;
                        break;
                    }
                    case 6: {
                        double price = utils::getDouble("Enter new ticket price: ", 2);
                        bus->price = price;
                        cout << "Succesfully changed ticket price to " << price;
                        break;
                    }
                }
                break;
            }
            case 3: {
                this->manage_buses();
                return;
            }
            case 4: {
                return;
            }
        }
    }
}

Administrator::Administrator(string json): User(json) {}

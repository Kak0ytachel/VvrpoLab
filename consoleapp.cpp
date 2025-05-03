#include "consoleapp.h"
#include "busroute.h"
#include "user.h"
#pragma once

ConsoleApp::ConsoleApp(string filename): filename(filename) {
    bool flag = this->get_data();
    if (!flag) {
        cout << "Unable to read data file" << endl;
        this->filename = "data.dat";
    }
}

BusRoute* ConsoleApp::get_bus(int route_id) {
    for (int i = 0; i < this->buses.size(); i++) {
        if (this->buses[i]->routeId == route_id) {
            cout << "searching " << this->buses[i]->routeId << endl;
            return this->buses[i];
        }
    }
    // should never happen
    return this->buses[0];

}

vector<BusRoute*> ConsoleApp::get_all_buses() {
    return this->buses;
}

void ConsoleApp::load_file() {
    
}

bool ConsoleApp::get_data() {
    ifstream fin;
    fin.open(this->filename);
    if (fin.is_open()) {
        string line;
        getline(fin, line);
        // TODO

        return true;
    } else {
        return false;
    }

}

void ConsoleApp::save_data() {
    ofstream fout;
    fout.open(this->filename);
    
}

void ConsoleApp::run() {
    bool exitFlag = false;
    while (!exitFlag) {
        string login = utils::getString("Enter login");
        string password = utils::getString("Enter password");
        string salted_password = utils::encrypt(password);
        User *user = nullptr;
        for (int i = 0; i < this->users.size(); i++) {
            if (this->users[i]->check_credentials(login, salted_password)) {
                user = this->users[i];
                break;
            }
        }
        if (user != nullptr) {
            user->main();
            exitFlag = true;
        } else {
            cout << "Wrong login or password. Please try again" << endl;
        }
    }
}


int ConsoleApp::create_unique_route_id() {
    return this->next_route_id++;
}

void ConsoleApp::add_route(BusRoute *bus) {
    this->buses.push_back(bus);
}

// string serialize() {
//     // JsonSerializer serializer = JsonSerializer();
//     // serializer.serialize_vector<User>("users", users);
//     // serializer.serialize_vector
// }

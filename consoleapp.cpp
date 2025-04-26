#include "consoleapp.h"
#pragma once

ConsoleApp::ConsoleApp(string filename): filename(filename) {
    bool flag = this->get_data();
    if (!flag) {
        cout << "Unable to read data file" << endl;
        this->filename = "data.dat";
    }
}

string ConsoleApp::encrypt(string pass) {
    return pass;
    // TODO replace
}

// BusRoute* get_bus(int route_id) {
//     // for (int i = 0; i < this->buses.size(); i++) {
//     //     if (this->buses[i]->routeId == route_id) {
//     //         return this->buses[i];
//     //     }
//     // }
// }

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
    string login = utils::getString("Enter login");
    string password = utils::getString("Enter password");
    string salted_password = this->encrypt(password);
    // User *user = nullptr;
    // for (int i = 0; i < this->users.size(); i++) {
    //     if (this->users[i]->check_credentials(login, salted_password)) {
    //         user = this->users[i];
    //     }
    // }
    // user->main();
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

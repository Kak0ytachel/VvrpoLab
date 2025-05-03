#include "consoleapp.h"
#include "busroute.h"
#include "user.h"
#pragma once

ConsoleApp::ConsoleApp(string filename): filename(filename) {
    string json = this->get_data();
    if (json.size() == 0) {
        cout << "Unable to read data file" << endl;
        this->filename = "data.dat";
        User *u = new User("Default", "user", "user");
        Administrator *a = new Administrator("Admin", "admin", "admin");
        this->users.push_back(u);
        this->users.push_back(a);
        return;
    }
    JsonDeserializer deserializer = JsonDeserializer(json);
    this->users = deserializer.deserialize_user_vector("users");
    this->buses = deserializer.deserialize_vector<BusRoute>("buses");
    this->next_route_id = deserializer.deserialize_int("next_route_id");
    
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

string ConsoleApp::get_data() {
    ifstream fin;
    fin.open(this->filename);
    if (fin.is_open()) {
        string line;
        getline(fin, line);
        // TODO

        return line;
    } else {
        return "";
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

string ConsoleApp::serialize() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_vector<User>("users", this->users);
    serializer.serialize_vector<BusRoute>("buses", this->buses);
    serializer.serialize_int("next_route_id", this->next_route_id);
    return serializer.get_result();
}

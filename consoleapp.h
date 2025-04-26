#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "utils.h"
#pragma once

using namespace std;

class User;
class BusRoute;

class ConsoleApp {
    vector<User*> users;
    vector<BusRoute*> buses;
    int next_route_id = 1001;
    string filename;
public:    
    ConsoleApp(string filename);

    string encrypt(string pass);

    // BusRoute* get_bus(int route_id) {
    //     // for (int i = 0; i < this->buses.size(); i++) {
    //     //     if (this->buses[i]->routeId == route_id) {
    //     //         return this->buses[i];
    //     //     }
    //     // }
    // }
    
    void load_file();

    bool get_data();

    void save_data();

    void run();

    int create_unique_route_id();

    void add_route(BusRoute *bus);
};
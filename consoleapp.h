#include "user.h"
#include "busroute.h"
#pragma once

class ConsoleApp {
    vector<User*> users;
    vector<BusRoute*> buses;
    int next_route_id = 1001;
    string filename;
public:    
    ConsoleApp(string filename);

    string encrypt(string pass);

    // BusRoute* get_bus(int route_id);
    
    void load_file();

    bool get_data();

    void save_data();

    void run();

    int create_unique_route_id();

    void add_route(BusRoute *bus);

    // string serialize();
};

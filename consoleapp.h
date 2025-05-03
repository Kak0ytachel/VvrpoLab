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
    vector<BusRoute*> buses;
    int next_route_id = 1001;
    string filename;
public:    
    
    vector<User*> users;
    ConsoleApp(string filename);

    BusRoute* get_bus(int route_id);
    
    vector<BusRoute*> get_all_buses();

    void load_file();

    string get_data();

    void save_data();

    void run();

    int create_unique_route_id();

    void add_route(BusRoute *bus);

    string serialize();
};

ConsoleApp *app = nullptr;

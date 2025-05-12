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

    ConsoleApp(string filename); //  инициализация

    BusRoute* get_bus(int route_id); // возвращает автобусный маршрут по номеру
    
    vector<BusRoute*> get_all_buses(); // возвращает все автобусы

    string get_data(); // получает данные из файла

    void save_data(); // сохраняет данные в файл

    void run(); // основной цикл программы

    int create_unique_route_id(); // создает новый уникальный номер маршрута

    void add_route(BusRoute *bus); // добавляет маршрут в словарь

    string serialize(); // сереализация
};

ConsoleApp *app = nullptr;

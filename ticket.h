#include <string>
#include "jsondeserializer.h"
#pragma once

class BusRoute;

class Ticket{
public:
    int routeId;
    int quantity;
    int is_canceled = 0;

    Ticket(int routeId, int quantity); // стандартная инициализация

    void cancel(); // отмена билета

    BusRoute* get_bus(); // получение маршрута по билету

    string serialize(); // сериализация

    Ticket(string json); // инициализация при дересериализации
};
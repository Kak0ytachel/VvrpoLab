#include <string>
#include "datetime.h"
#include "ticket.h"
#pragma once
using namespace std;


class BusRoute{
public:
    string origin;
    string destination;
    Datetime departure;
    Datetime arrival;
    int seatsTotal;
    int ticketsLeft;
    int routeId;
    double price;

    BusRoute(string origin, string destination, Datetime departure, Datetime arrival, int tickets, double price); // стандартная инициализация

    Ticket* buy_ticket(int quantity); // покупка билета 

    void cancel_ticket(Ticket *t); // отмена билета

    string serialize(); // cереализация

    BusRoute(string json); // инициализация при дересериализации
};
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

    BusRoute(string origin, string destination, Datetime departure, Datetime arrival, int tickets);

    Ticket buy_ticket(int quantity);

    void cancel_ticket(Ticket t);

    string serialize();

    BusRoute(string json);
};
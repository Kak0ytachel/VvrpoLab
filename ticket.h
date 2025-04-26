#include <string>
#include "jsondeserializer.h"
#pragma once

class Ticket{
public:
    int routeId;
    int quantity;
    int is_canceled = 0;

    Ticket(int routeId, int quantity);

    void cancel();

    // BusRoute* get_bus();

    string serialize();

    Ticket(string json);
};
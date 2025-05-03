#include "busroute.h"
#include "jsonserializer.h"
#include "consoleapp.h"

extern ConsoleApp *app;

BusRoute::BusRoute(string origin, string destination, Datetime departure, Datetime arrival, int tickets): 
    origin(origin), destination(destination), departure(departure), arrival(arrival), seatsTotal(tickets), ticketsLeft(tickets)  {
    
    this->routeId = app->create_unique_route_id();
    app->add_route(this);
}

Ticket* BusRoute::buy_ticket(int quantity) {
    if (quantity <= this->ticketsLeft) {
        this->ticketsLeft -= quantity;
        return new Ticket(this->routeId, quantity);
    } else {
        return new Ticket(this->routeId, 0);
    }
}

void BusRoute::cancel_ticket(Ticket *t) {
    if (t->routeId == this->routeId) {
        if (t->is_canceled == 0) {
            this->ticketsLeft += t->quantity;
            t->is_canceled = 1;
            t->quantity = 0;
        }
    }
}

string BusRoute::serialize() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_string("origin", this->origin);
    serializer.serialize_string("destination", this->destination);
    serializer.serialize_dt("departure", this->departure);
    serializer.serialize_dt("arrival", this->arrival);
    serializer.serialize_int("seatsTotal", this->seatsTotal);
    serializer.serialize_int("ticketsLeft", this->ticketsLeft);
    serializer.serialize_int("routeId", this->routeId);
    return serializer.get_result();
}

BusRoute::BusRoute(string json) {
    JsonDeserializer deserializer = JsonDeserializer(json);
    this->origin = deserializer.deserialize_string("origin");
    this->destination = deserializer.deserialize_string("destination");
    this->departure = deserializer.deserialize_dt("departure");
    this->arrival = deserializer.deserialize_dt("arrival");
    this->seatsTotal = deserializer.deserialize_int("seatsTotal");
    this->ticketsLeft = deserializer.deserialize_int("ticketsLeft");
    this->routeId = deserializer.deserialize_int("routeId");
}

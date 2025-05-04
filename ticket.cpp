#include "ticket.h"
#include "jsonserializer.h"
#include "consoleapp.h"
#include "busroute.h"
#pragma once

extern ConsoleApp *app;

Ticket::Ticket(int routeId, int quantity): routeId(routeId), quantity(quantity) {}

void Ticket::cancel() {
    this->get_bus()->cancel_ticket(this);
}

BusRoute* Ticket::get_bus() {
    return app->get_bus(this->routeId);
}

string Ticket::serialize() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_int("routeId", this->routeId);
    serializer.serialize_int("quantity", this->quantity);
    serializer.serialize_int("is_canceled", this->is_canceled);
    return serializer.get_result();
}

Ticket::Ticket(string json) {
    // cout << "Deserializing Ticket" << endl;
    JsonDeserializer deserializer = JsonDeserializer(json);
    this->routeId = deserializer.deserialize_int("routeId");
    this->quantity = deserializer.deserialize_int("quantity");
    this->is_canceled = deserializer.deserialize_int("is_canceled");
}

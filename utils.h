#include <string>
#include "datetime.h"
using namespace std;

#pragma once

class BusRoute;
class Ticket;

namespace utils{
    int getInt(int min_val, int max_val, string message);

    string getString(string message);

    Datetime getDate(string message);

    string encrypt(string pass);

    string centered(string s, int l);

    void showBuses(vector<BusRoute*> buses);

    void showTickets(vector<Ticket*> tickets);
}